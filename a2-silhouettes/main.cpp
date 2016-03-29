#include <iostream>
#include <string>
#include <QImage>
#include <QColor>
#include <QtGui>
#include <QWindow>
using namespace std;
//The variable specifies the color threshold for image binarization
const int THRESHOLD_COLOR = 9;
//input: pointer to array
//output: number of silhouettes
int countingSilhouettes(string fileName);

int main() {
    //@param fileName - name of the input image
    string fileName;
    cout << "Please, enter name of the image: \n"<<endl;
    cin >> fileName;

    cout << "There is/are " << countingSilhouettes(fileName) <<" silhouette/s on the image." << endl;
    return 0;
}

//void Binarization(QImage *img,  int* bitMap)
//{
//    const int W = img->width();
//    const int H = img->height();
//    for(int i = 0; i < H; ++i){
//        bitMap[i] = new int[W];
//    }
//    int pixelRGB = 0;
//    for (int y=1; y<H; y++)
//    {
//        for (int x=1; x<W; x++)
//        {
////            RGBTRIPLE row;
//            QColor col;
////            int red = row.rgbtRed;
////            int green = row.rgbtGreen;
////            int blue = row.rgbtBlue;
//           pixelRGB =  img->pixel(x,y);
//            if ( pixelRGB > THRESHOLD_COLOR)
//            {
//                bitMap[x][y] = 0;
//                img->setPixel(x,y,col.rgb());
//            } else {
//                bitMap[x][y] = 1;
//                img->setPixel(x,y,col.rgb());
//            }
//        }
//    }
//}

void Fill(int x, int y, int oldVal, int newVal, int** bitMap)
{
//int W,H;
    if(x< 0 || y < 0 || (bitMap [x][y] != 0)){
       return;
    }
       else{
        bitMap [x][y] = newVal;
        //if( x > 0 )
            Fill(x + 1, y, oldVal,newVal, bitMap);
       // if( x < W)
            Fill(x - 1, y, oldVal,newVal, bitMap);
      //  if( y > 0 )
            Fill(x, y - 1, oldVal,newVal, bitMap);
      //  if( y < H )
            Fill(x, y + 1, oldVal,newVal, bitMap);
    }
}

/*
* The function counting the number of silhouettes.
*/
int countingSilhouettes(string fileName )
{
    // string fileName;
    getline(cin,fileName);
    //string filename = filename.fromStdString(fileName);
    QImage *image = new QImage(fileName.c_str());
    int imageHeight = (int)image->height();
    int imageWidth = (int)image->width();
//    QWindow *qw;
//    QBuffer *buf;
   // buf->objectName(fileName);
//    qw->show();
//    qw->setObjectName(fileName.c_str());
    //creating array for bitMap
    int** bitMap = new int*[imageWidth];
//    for (int x = 0; x < imageWidth; x++) {
//        bitMap[x] = new int[imageHeight];
//    }
    //Call function Binarization
//    Binarization(image,bitMap);
    int silhouettesOnImg;// silhouettes counter
    //@param - The old value for item
    int oldVal = 1;
    //@param - The new value for item
    int newVal = 1;
    //search silhouettes on bitMap
    for (int y = 0; y < imageHeight; y++) {
            for (int x = 0; x < imageWidth; x++){
            if(bitMap[x][y] == 0){
                newVal++;
                //Call Fill function
                Fill(x,y,oldVal,newVal, bitMap);
                silhouettesOnImg++;
}
            }
    }
    for(int y = 0; y < imageHeight; y++){
        delete[]bitMap[y];
    }
    delete []bitMap;
    delete image;
    return silhouettesOnImg;
}
