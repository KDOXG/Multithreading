#pragma pack(1)
#include "bmp.h"

tagBITMAP::tagBITMAP(int n)
{
    this->pBMPFileHeader = new tagBITMAPFILEHEADER();
    this->pBMPInfoHeader = new tagBITMAPINFOHEADER();
    this->buffer = new std::vector<char>(n);
}

tagBITMAP::~tagBITMAP()
{
    delete this->pBMPFileHeader;
    delete this->pBMPInfoHeader;
    delete this->buffer;
}

ImageData::ImageData(tagBITMAP *info)
{
    if (!info)
    {
        this->info = NULL;
        this->width = 0;
        this->height = 0;
        this->R = NULL;
        this->G = NULL;
        this->B = NULL;
        this->outR = NULL;
        this->outG = NULL;
        this->outB = NULL;
        return;
    }
    this->info = info;
    this->width = info->pBMPInfoHeader->biWidth;
    this->height = info->pBMPInfoHeader->biHeight;
    this->R = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height));
    this->G = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height));
    this->B = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height));
    this->outR = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height));
    this->outG = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height));
    this->outB = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height));
}

ImageData::~ImageData()
{
    delete this->info;
    delete R;
    delete G;
    delete B;
    delete outR;
    delete outG;
    delete outB;
}

tagBITMAP* readBMP(std::string filename)
{
    std::ifstream file(filename);
    tagBITMAP *tags = NULL;

    if (file) {
        file.seekg(0,std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0,std::ios::beg);

        tags = new tagBITMAP(length);
        file.read(tags->buffer->data(),length);

        tags->pBMPFileHeader = (tagBITMAPFILEHEADER *)(tags->buffer->data());
        tags->pBMPInfoHeader = (tagBITMAPINFOHEADER *)(tags->buffer->data() + sizeof(tagBITMAPFILEHEADER));
    }
    return tags;
}