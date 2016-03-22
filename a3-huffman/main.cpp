#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
using namespace std;
/*структуры или записи/structure or recording*/
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
    unsigned char varContCode;//variable contains code for recording the compressed file/переменная содержащая код для записи в сжатый файл

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

/* recursive function to create Huffman tree/рeкурсивная функция создания дерева Хаффмана*/
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
    else //Adding to the array to the right place Huffman tree element/внесение в массив в нужное место элемента дерева Хаффмана
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

/*The recursive encoding function/Рекурсивная функция кодирования*/
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
    FILE *fp,*fp2,*fp3; //pointers to files/указатели на файлы
    setlocale(LC_ALL,"Rus");
    char  infile[20];

    printf("Please, enter the name of the file: \n");

    fflush (stdin);
    gets(infile);
    fp = fopen(infile,"r");
    //Processing file read errors/Обработка ошибок чтения файла
    if (fp==NULL)
    {
        puts ("\nCould not open file");
        getchar();
        exit (1); //Exit with exit code 1/Выйти с кодом завершения 1
    }
    fflush(stdin);
    getchar();
    fp2 = fopen("output.txt","wb");//opening a file for writing binary code/открытие файла для записи бинарного кода
    fp3=fopen("teemp.txt","wb");//opening a file for writing the compressed file/открытие файла для записи сжатого файла

    int chh;  // variable for reading information from a file/переменная для чтения информации из файла
    int k=0; //the counter of the number of different letters, unique characters/счётчик количества различных букв, уникальных символов
    int kk=0; // the counter of the number of all the characters in a file/счётчик количества всех знаков в файле
    int fsize2=0;//the counter of the number of characters from 0 and 1 in the intermediate file teemp/ счётчик количества символов из 0 и 1 в промежуточном файле teemp
    int ts;//tail file size (that is not a multiple of 8 in the intermediate file)/размер хвоста файла (то, что не кратно 8 в промежуточном файле)
    int kolvo[256]={0};// initialize an array of the number of unique charactersинициализируем массив количества уникальных символов
    node simbols[256]={0}; //initialize an array of records/инициализируем массив записей
    node *pnode[256]; //initialize an array of pointers to records/инициализируем массив указателей на записи
    float frequencySum=0;//сумма частот встречаемости
    int mes[8];//array of 0 and 1
    char j=0;//An additional variable/дополнительная переменная
    //    node *nodebols=(node*)malloc(k*sizeof(node));//создание динамического массива структур simbols
    //    node **psum=(node**)malloc(k*sizeof(node*));//создание динамического массива указателей на simbols

    //Byte-by-byte reading file and drawing up table of occurrence/ Побайтное чтение файла и составление таблицы встречаемости
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

    //Calculation of frequency of occurrence/ Рассчёт частоты встречаемости
    for(int i=0;i<k;i++)
        simbols[i].freq=(float)kolvo[i]/kk;

    for(int i=0;i<k;i++) // entering of the address of records in an array of indexes/занесение адреса записей в массив указателей
        pnode[i]=&simbols[i];

    //Sort descending/Сортировка по убыванию
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

    node *root=makeTree(pnode,k);//call options to create Huffman tree/вызов функции создания дерева Хаффмана

    makeCodes(root);//receive call function code/вызов функции получения кода

    rewind(fp);//return a pointer to a file in the file beginning/возвращаем указатель в файле в начало файла
    //cycle for reading the source file code and write functions obtained in the intermediate file/  цикл для чтения исходного файла, и записи полученных в функциях кодов в промежуточный файл
    while((chh=fgetc(fp))!=EOF)
    {
        for(int i=0;i<k;i++)
            if(chh==simbols[i].ch)
                fputs(simbols[i].code,fp2);
    }
    fclose(fp2);
    {
        // Re-open the file with a binary code, but now reading/ Заново открываем файл с бинарным кодом, но теперь для чтения
        int i=0;
        fp2=fopen("teemp.txt","rb");
        //Read the size of the binary file (the number of characters in it)/Считываем размер бинарного файла(количество символов в нём)
        while((chh=fgetc(fp2))!=EOF)
            fsize2++;

        ts=fsize2%8;//find the remainder, the number of characters are not multiples of 8 (tail)/находим остаток, количество символов не кратных 8 (хвост)

        // Form the header byte compressed file through the field/формируем заголовок сжатого файла через поля байтов
        fwrite("compresing!!!",sizeof(char),24,fp3);//conditional signature/условная подпись
        fwrite(&k,sizeof(int),1,fp3);//the number of unique characters/количество уникальных символов
        fwrite(&ts,sizeof(int),1,fp3);//the value of the tail/величина хвоста
        //Written to a compressed file occurrence table/Записываем в сжатый файл таблицу встречаемости
        for(i=0;i<k;i++)
        {
            fwrite(&simbols[i].ch,sizeof(node),1,fp3);
            fwrite(&simbols[i].freq,sizeof(node),1,fp3);
        }

        rewind(fp2);//return a pointer to an intermediate file at the beginning of the file/возвращаем указатель в промежуточном файле в начало файла

        union code code1;//инициализируем переменную code1
        /*Read binary file, populating it consistently every 8 elements in an array for subsequent bit manipulation in uniting union/ Читаем бинарный файл, занося последовательно каждые 8 элементов в массив для последующей побитовой обработки в объединении union*/
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
        //Write the tail/Записываем хвост
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
