#include  <iostream>
#include "gwindow.h"
#include "gbufferedimage.h"
#include "gobjects.h"

using namespace std;

const int MIN_SILHOUETTE_SIZE = 100;// the minimum number of pixels required to determine the silhouette
const int BACKGROUND_COLOR = 13750737; // color for background (HEX #d1d1d1)
//function prototypes

//@param fileName - name of the input image
int countingSilhouettes(string fileName);

/*Binarization is the process of converting a pixel image to a binary image.*/
void Binarization(GBufferedImage *bufImg,  int **bitMap);
/*
*@param bitMap - a bitmap of image
*@param bufImage - matrix of colored pixels
*@param imgWidth - width of the image
*@param imgHeight - height of the image
*/

void Fill(int x, int y, int oldVal, int newVal, int **bitMap, int W, int H, int &silhouetteSize);
/*
*@param x, y - coordinates of the bitmap
*@param oldVal - label used for marking pixels of the silhouettes
*@param newVal - label used for separation pixels of the silhouettes
*@param silhouetteSize - the minimum size of the silhouette to be taken into account
*/

/*Binarization process*/
void Binarization(GBufferedImage *bufImg,  int **bitMap)
{
    int imgHeight = (int)bufImg->getHeight();
    int imgWidth = (int)bufImg->getWidth();
    int pixelRGB = 0;
    for (int y=1; y<imgHeight; y++)
    {
        for (int x=1; x<imgWidth; x++)
        {
            pixelRGB =  bufImg->getRGB(x,y);
            if ( pixelRGB > BACKGROUND_COLOR)
            {
                bitMap[x][y] = 0;
            } else {
                bitMap[x][y] = 1;
            }
        }
    }
}

//recursive function that found filling set in the binary plane
void Fill(int x, int y, int oldVal, int newVal, int **bitMap, int W, int H, int & silhouetteSize) {
    if (x >= 0 && x < W && y >= 0 && y < H && bitMap[x][y] == oldVal && bitMap[x][y] != newVal) {
        silhouetteSize++;
        bitMap[x][y] = newVal;
        Fill(x, y+1, oldVal, newVal, bitMap, W, H, silhouetteSize);
        Fill(x, y-1, oldVal, newVal, bitMap, W, H, silhouetteSize);
        Fill(x-1, y, oldVal, newVal, bitMap, W, H, silhouetteSize);
        Fill(x+1, y, oldVal, newVal, bitMap, W, H, silhouetteSize);
    }
}


int countingSilhouettes(string fileName) {
    GBufferedImage *bufImg = new GBufferedImage(0, 0, img->getWidth(), img->getHeight()); //matrix size is the size of the image
    bufImg->load(fileName);
    GImage *img;
    img = new GImage(fileName);
    //object window
    GWindow window(img->getWidth(), img->getHeight());// window size is the size of the image
    window.add(img);
    //buffer for image pixel reading
    bufImg->load(fileName);
    //image width and height
    int imgHeight = (int)bufImg->getHeight();
    int imgWidth = (int)bufImg->getWidth();
    //create a bitmap array
    int **bitMap = new int *[imgWidth];

    for (int x = 0; x < imgWidth; x++) {
        bitMap[x] = new int[imgHeight];
    }

    Binarization(bufImg, bitMap);// binarization of the image
    int oldVal = 1; // new value of the pixel
    int newVal = 1;// old value of the pixel
    int silhouettesOnImg = 0;// silhouettes counter

    for (int x = 1; x < imgWidth; x++) {
        for (int y = 1; y < imgHeight; y++) {
            if (bitMap[x][y] == 1) {
                newVal++;
                int silhouetteSize = 0;
                Fill(x, y, oldVal, newVal, bitMap, imgWidth, imgHeight, silhouetteSize);

                // if the size of the selected area is less than MIN_SILHOUETTE_SIZE,
                // we do not consider this area a separate silhouette
                if (silhouetteSize >= MIN_SILHOUETTE_SIZE) {
                    silhouettesOnImg++;
                }
            }
        }
    }

    // clean memory
    for (int x = 0; x < imgWidth; x++) {
        delete[]bitMap[x];
    }

    delete []bitMap;
    delete img;
    delete bufImg;
    return silhouettesOnImg;
}

int main() {
    string fileName;
    cout << "Please, enter name of the image: ";
    cin >> fileName;
    cout << "silhouette: There is/are " << countingSilhouettes(fileName) << " silhouette/s on the image." << endl;
    return 0;
}
