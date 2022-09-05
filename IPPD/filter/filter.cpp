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

    tagBITMAP *fileInfo = ReadBMP(string(argv[1]));
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

    #pragma omp parallel for
    for(int i = 0; i < img->width; i++) {
        #pragma omp parallel for shared(img)
        for (int j = 0; j < img->height; j++) {
            img->R->at(i).at(j) = j;
            img->G->at(i).at(j) = j;
            img->B->at(i).at(j) = j;
        }
    }

    img->applyFilter(passabaixa, passabaixaTotal);

    cout << "Filter succesful!\n";

    for (int i = 0; i < N ; i++, cout << "\n") {
        for (int j = 0; j < M; j++)
            cout << img->outR->at(i).at(j) << " ";
    }
    
    delete img;

    return 0;
}