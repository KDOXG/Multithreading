#include "filter.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <iterator>
#include <bitset>
#include <omp.h>
#define N 50
#define M 50

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc != 2) return -1;

    tagBITMAP *fileInfo = readBMP(string(argv[1]));
    cout << "Read image succesful!\n";
    ImageData *img = new ImageData(fileInfo);
    cout << "Save image succesful!\n";

    if (fileInfo)
    {    
        cout << "File read succesful!\n";
        cout << "Struct tagBITMAPFILEHEADER\n";
        cout << "\tWORD bfType: " << fileInfo->pBMPFileHeader->bfType << '\n';
        cout << "\tDWORD bfSize: " << fileInfo->pBMPFileHeader->bfSize << '\n';
        cout << "\tWORD bfReserved1: " << fileInfo->pBMPFileHeader->bfReserved1 << '\n';
        cout << "\tWORD bfReserved2: " << fileInfo->pBMPFileHeader->bfReserved2 << '\n';
        cout << "\tDWORD bfOffBits: " << fileInfo->pBMPFileHeader->bfOffBits << '\n';

        cout << "Struct tagBITMAPINFOHEADER\n";
        cout << "\tDWORD biSize: " << fileInfo->pBMPInfoHeader->biSize << '\n';
        cout << "\tLONG biWidth: " << fileInfo->pBMPInfoHeader->biWidth << '\n';
        cout << "\tLONG biHeight: " << fileInfo->pBMPInfoHeader->biHeight << '\n';
        cout << "\tWORD biPlanes: " << fileInfo->pBMPInfoHeader->biPlanes << '\n';
        cout << "\tWORD biBitCount: " << fileInfo->pBMPInfoHeader->biBitCount << '\n';
        cout << "\tDWORD biCompression: " << fileInfo->pBMPInfoHeader->biCompression << '\n';
        cout << "\tDWORD biSizeImage: " << fileInfo->pBMPInfoHeader->biSizeImage << '\n';
        cout << "\tLONG biXPelsPerMeter: " << fileInfo->pBMPInfoHeader->biXPelsPerMeter << '\n';
        cout << "\tLONG biYPelsPerMeter: " << fileInfo->pBMPInfoHeader->biYPelsPerMeter << '\n';
        cout << "\tDWORD biClrUsed: " << fileInfo->pBMPInfoHeader->biClrUsed << '\n';
        cout << "\tDWORD biClrImportant: " << fileInfo->pBMPInfoHeader->biClrImportant << '\n';
    }
    int n = 1, m = 1;

    #pragma omp parallel for
    for(int i = 0; i < img->width; i++) {
        #pragma omp parallel for shared(img)
        for (int j = 0; j < img->height; j++) {
            img->R->at(i).at(j) = j*256;
            img->G->at(i).at(j) = j;
            img->B->at(i).at(j) = j;
        }
    }

    // filterIterative(img);

    cout << "Filter succesful!\n";

    // for (int i = 0; i < N ; i++)
    //     for (int j = 0; j < M; j++)
    //         cout << outR[i][j] << ( (j < M - 1) ? " " : "\n" );
    
    delete img;

    return 0;
}

/*
void filterIterative(ImageData *img)
{
    unsigned int sumR = 0;
    bitset<2> posx, posy;

    cout << "I'm in\n";

    //#pragma omp parallel for private(posx)
    for (int i = 0; i < hx; i++)
    {
        posx[0] = !(i == 0);
        posx[1] = !(i == hx-1);
        //#pragma omp parallel for private(posy, sumR)
        for (int j = 0; j < hy; j++)
        {
            posy[0] = !(j == 0);
            posy[1] = !(j == hy-1);
            // cout << sumR << endl;
            sumR += R[i-1*posx.test(0)]     [j-1*posy.test(0)]  * passabaixa[0][0] * posx.test(0) * posy.test(0);
            // cout << sumR << endl;
            sumR += R[i-1*posx.test(0)]     [j]                 * passabaixa[0][1] * posx.test(0);
            sumR += R[i-1*posx.test(0)]     [j+1*posy.test(1)]  * passabaixa[0][2] * posx.test(0) * posy.test(1);
            // cout << sumR << endl;
            sumR += R[i]                    [j-1*posy.test(0)]  * passabaixa[1][0] * posy.test(0);
            sumR += R[i]                    [j]                 * passabaixa[1][1];
            sumR += R[i]                    [j+1*posy.test(1)]  * passabaixa[1][2] * posy.test(1);
            // cout << sumR << endl;
            sumR += R[i+1*posx.test(1)]     [j-1*posy.test(0)]  * passabaixa[2][0] * posx.test(1) * posy.test(0);
            sumR += R[i+1*posx.test(1)]     [j]                 * passabaixa[2][1] * posx.test(1);
            sumR += R[i+1*posx.test(1)]     [j+1*posy.test(1)]  * passabaixa[2][2] * posx.test(1) * posy.test(0);
            // cout << sumR << endl;
            // cout << "-----------------" << endl;
            
            outR[i][j] = sumR / passabaixaTotal;

            sumR = 0;

        }
        //cout << "Ok...\n";
    }

    return;

}
*/