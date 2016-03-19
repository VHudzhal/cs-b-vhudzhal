#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
using namespace std;
/*structure or recording*/
struct node
{
    unsigned char ch;
    float freq;
    char code[255];
    node *left;
    node *right;
};

union code
{
    unsigned char varContCode;//variable contains code for recording the compressed file

    struct byte
    {
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
        unsigned b8:1;
    }
    byte;
};

/* recursive function to create Huffman tree*/
node *makeTree(node *pnode[],int k)
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->freq=pnode[k-1]->freq+pnode[k-2]->freq;
    temp->code[0]=0;
    temp->left=pnode[k-1];
    temp->right=pnode[k-2];

    if(k==2)
        return temp;
    else //Adding to the array to the right place Huffman tree element
    {
        for(int i=0;i<k;i++)
            if (temp->freq>pnode[i]->freq)
            {
                for(int j=k-1;j>i;j--)
                    pnode[j]=pnode[j-1];

                pnode[i]=temp;
                break;
            }
    }
    return makeTree(pnode,k-1);
}

/*The recursive encoding function*/
void makeCodes(node *root)
{
    if(root->left)
    {
        strcpy(root->left->code,root->code);
        strcat(root->left->code,"0");
        makeCodes(root->left);
    }
    if(root->right)
    {
        strcpy(root->right->code,root->code);
        strcat(root->right->code,"1");
        makeCodes(root->right);
    }
}


int main ()
{
    FILE *fp,*fp2,*fp3; //pointers to files
    setlocale(LC_ALL,"Rus");
    char  infile[20];

    printf("Please, enter the name of the file: \n");

    fflush (stdin);
    gets(infile);
    fp = fopen(infile,"r");
    //Processing file read errors/
    if (fp==NULL)
    {
        puts ("\nCould not open file");
        getchar();
        exit (1); //Exit with exit code 1
    }
    fflush(stdin);
    getchar();
    fp2 = fopen("output.txt","wb");//opening a file for writing binary code
    fp3=fopen("teemp.txt","wb");//opening a file for writing the compressed file

    int chh;  // variable for reading information from a file
    int k=0; //the counter of the number of different letters, unique characters
    int kk=0; // the counter of the number of all the characters in a file
    int fsize2=0;//the counter of the number of characters from 0 and 1 in the intermediate file teemp
    int ts;//tail file size (that is not a multiple of 8 in the intermediate file)
    int kolvo[256]={0};// initialize an array of the number of unique characters
    node simbols[256]={0}; //initialize an array of records
    node *pnode[256]; //initialize an array of pointers to records
    float frequencySum=0;//Sum of the frequencies of occurrence
    int mes[8];//array of 0 and 1
    char j=0;//An additional variable

    /*Byte-by-byte reading file and drawing up table of occurrence*/
    while((chh=fgetc(fp))!=EOF)
    {
        for(int j=0; j<256; j++)
        {
            if (chh==simbols[j].ch)
            {
                kolvo[j]++;
                kk++;
                break;
            }
            if (simbols[j].ch==0)
            {
                simbols[j].ch=(unsigned char)chh;
                kolvo[j]=1;
                k++; kk++;
                break;
            }
        }
    }

    //Calculation of frequency of occurrence
    for(int i=0;i<k;i++)
        simbols[i].freq=(float)kolvo[i]/kk;

    for(int i=0;i<k;i++) // entering of the address of records in an array of indexes
        pnode[i]=&simbols[i];

    //Sort descending
    node tempp;
    for(int i=1;i<k;i++)
        for(int j=0;j<k-1;j++)
            if(simbols[j].freq<simbols[j+1].freq)
            {
                tempp=simbols[j];
                simbols[j]=simbols[j+1];
                simbols[j+1]=tempp;
            }

    for(int i=0;i<k;i++)
    {
        frequencySum+=simbols[i].freq;
        printf("Ch= %d\tFreq= %f\tPPP= %c\t\n",simbols[i].ch,simbols[i].freq,pnode[i]->ch,i);
    }
    printf("\n Words = %d\tfrequencySum=%f\n",kk,frequencySum);

    node *root=makeTree(pnode,k);//call options to create Huffman tree

    makeCodes(root);//receive call function code

    rewind(fp);//return a pointer to a file in the file beginning
    //cycle for reading the source file code and write functions obtained in the intermediate file
    while((chh=fgetc(fp))!=EOF)
    {
        for(int i=0;i<k;i++)
            if(chh==simbols[i].ch)
                fputs(simbols[i].code,fp2);
    }
    fclose(fp2);
    {
        // Re-open the file with a binary code, but now reading
        int i=0;
        fp2=fopen("teemp.txt","rb");
        //Read the size of the binary file (the number of characters in it)
        while((chh=fgetc(fp2))!=EOF)
            fsize2++;

        ts=fsize2%8;//find the remainder, the number of characters are not multiples of 8 (tail)

        // Form the header byte compressed file through the field
        fwrite("compresing!!!",sizeof(char),24,fp3);//conditional signature
        fwrite(&k,sizeof(int),1,fp3);//the number of unique characters
        fwrite(&ts,sizeof(int),1,fp3);//the value of the tail
        //Written to a compressed file occurrence table
        for(i=0;i<k;i++)
        {
            fwrite(&simbols[i].ch,sizeof(node),1,fp3);
            fwrite(&simbols[i].freq,sizeof(node),1,fp3);
        }

        rewind(fp2);//return a pointer to an intermediate file at the beginning of the file

        union code code1;//initialize variable code1
        /*Read binary file, populating it consistently every 8 elements in an array for subsequent bit manipulation in uniting union*/
        j=0;
        for(int i=0;i<fsize2-ts;i++)
        {
            mes[j]=fgetc(fp2);
            if(j==8)
            {
                code1.byte.b1=mes[0]-'0';
                code1.byte.b2=mes[1]-'0';
                code1.byte.b3=mes[2]-'0';
                code1.byte.b4=mes[3]-'0';
                code1.byte.b5=mes[4]-'0';
                code1.byte.b6=mes[5]-'0';
                code1.byte.b7=mes[6]-'0';
                code1.byte.b8=mes[7]-'0';
                fputc(code1.varContCode,fp3);
                j=0;
            }
            j++;
        }
        //Write the tail
        j=0;
        for(int i=0;i<=ts;i++)
        {
            mes[j]=fgetc(fp2);
            if(j==ts)
            {
                code1.byte.b1=mes[0]-'0';
                code1.byte.b2=mes[1]-'0';
                code1.byte.b3=mes[2]-'0';
                code1.byte.b4=mes[3]-'0';
                code1.byte.b5=mes[4]-'0';
                code1.byte.b6=mes[5]-'0';
                code1.byte.b7=mes[6]-'0';
                code1.byte.b8=mes[7]-'0';
                fputc(code1.varContCode,fp3);
            }
            j++;
        }
    }

    int choice;

    printf  ("\n Please enter next command:\n");
    cout<<"exit - close program\n";
    cout<<"output - open and read file 'output.txt\n";
    cout<<"teemp - open and read file 'teemp.txt' \n";
    cin >> choice;

    switch(choice)
    {

    case '1':
    {
        char outfile[20];
        cin>>outfile;
        fflush (stdin);
        gets(outfile);
        fp2 = fopen(outfile,"r+b");
        if (fp2==NULL) {
            printf ("\ncould not open file");
            getchar();
            exit (1); //Exit with exit code 1
        }
    }
        break;

    case '2':
    {
        char teempfile[30];
        cin>>teempfile;
        fflush (stdin);
        gets(teempfile);
        fp2 = fopen(teempfile,"r+b");
        if (fp2==NULL) {
            printf ("\ncould not open file");
            getchar();
            exit (1); //Exit with exit code 1
            break;
        }
    default:
        {
            fcloseall;
            break;
        }
            return 0;
        }
    }
}
