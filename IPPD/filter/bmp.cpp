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

void ImageData::applyFilter(const unsigned short int *mask)
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