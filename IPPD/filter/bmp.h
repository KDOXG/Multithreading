#pragma once

#include <vector>
#include <string>
#include <fstream>

typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef unsigned short int uint16_t;

struct tagBITMAPFILEHEADER
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};

struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

struct tagBITMAP
{
    tagBITMAPFILEHEADER *pBMPFileHeader;
    tagBITMAPINFOHEADER *pBMPInfoHeader;
    std::vector<char> *buffer;

    tagBITMAP(int n);
    ~tagBITMAP();
};

struct ImageData
{
    tagBITMAP *info;
    int width;
    int height;
    std::vector<std::vector<uint16_t>> *R, *G, *B;
    std::vector<std::vector<uint16_t>> *outR, *outG, *outB;

    ImageData(tagBITMAP *info);
    ~ImageData();
    void applyFilter(const unsigned short int *mask, const unsigned short int maskTotal);
};

tagBITMAP* ReadBMP(std::string filename);