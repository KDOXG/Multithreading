#pragma pack(1)
#include "bmp.h"
#include <bitset>
#include <omp.h>

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
    this->R = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height, 0));
    this->G = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height, 0));
    this->B = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height, 0));
    this->outR = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height, 0));
    this->outG = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height, 0));
    this->outB = new std::vector<std::vector<uint16_t>>(this->width,std::vector<uint16_t>(this->height, 0));
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

void ImageData::applyFilter(const unsigned short int mask[][3], const unsigned short int maskTotal)
{
    unsigned int sumR = 0, sumG = 0, sumB = 0;
    std::bitset<2> posx, posy;

    // std::cout << "I'm in\n";

    #pragma omp parallel for private(posx)
    for (int i = 0; i < this->width; i++)
    {
        posx[0] = !(i == 0);
        posx[1] = !(i == this->width-1);
        #pragma omp parallel for firstprivate(posy, sumR)
        for (int j = 0; j < this->height; j++)
        {
            posy[0]= !(j == 0);
            posy[1]= !(j == this->height-1);
            // cout << sumR << endl;
            sumR += this->R->at(i-1*posx.test(0)).at(j-1*posy.test(0)) * mask[0][0] * posx.test(0) * posy.test(0);
            // cout << sumR << endl;
            sumR += this->R->at(i-1*posx.test(0)).at(j) * mask[0][1] * posx.test(0);
            sumR += this->R->at(i-1*posx.test(0)).at(j+1*posy.test(1)) * mask[0][2] * posx.test(0) * posy.test(1);
            // cout << sumR << endl;
            sumR += this->R->at(i).at(j-1*posy.test(0)) * mask[1][0] * posy.test(0);
            sumR += this->R->at(i).at(j) * mask[1][1];
            sumR += this->R->at(i).at(j+1*posy.test(1)) * mask[1][2] * posy.test(1);
            // cout << sumR << endl;
            sumR += this->R->at(i+1*posx.test(1)).at(j-1*posy.test(0)) * mask[2][0] * posx.test(1) * posy.test(0);
            sumR += this->R->at(i+1*posx.test(1)).at(j) * mask[2][1] * posx.test(1);
            sumR += this->R->at(i+1*posx.test(1)).at(j+1*posy.test(1)) * mask[2][2] * posx.test(1) * posy.test(0);
            // cout << sumR << endl;
            // cout << "-----------------" << endl;
            
            this->outR->at(i).at(j) = sumR / maskTotal;

            sumR = 0;
            sumG = 0;
            sumB = 0;

        }
        //cout << "Ok...\n";
    }

    return;
}

tagBITMAP* ReadBMP(std::string filename)
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