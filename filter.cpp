#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <bitset>
#include <omp.h>
#define N 10
#define M 10
#define W1 1
#define W2 3
#define W3 9

using namespace std;

unsigned short int R[N][M], G[N][M], B[N][M];
unsigned short int outR[N][M], outG[N][M], outB[N][M];

const unsigned short int passabaixa[3][3] = {{W1, W2, W1}, {W2, W3, W2}, {W1, W2, W1}};
const unsigned short int passabaixaTotal = 25;

unsigned char* ReadBMP(char* filename);

void filterRecursive(int lx, int hx, int ly, int hy);
void filterIterative(int lx, int hx, int ly, int hy);

int main(int argc, char* argv[]) {
    
    // if (argc != 2) return -1;
    
    // ifstream *imagem = new ifstream(argv[1], ios::binary);
    
    // vector<char> *bytes = new vector<char>(
    //         (istreambuf_iterator<char>(*imagem)),
    //         (istreambuf_iterator<char>()));

    // string *bytes = new string((char*)ReadBMP(argv[1]));

    // imagem->close();

    // cout << bytes->size() << endl << 1920*3 << endl << 1280*3 << endl;

    // delete(bytes);

    #pragma omp for
    for(int i = 0; i < N; i++) {
        #pragma omp for
        for (int j = 0; j < M; j++) {
            R[i][j] = j;
            G[i][j] = j;
            B[i][j] = j;
        }
    }

    //filterRecursive(0, N, 0, M);

    filterIterative(0, N-1, 0, M-1);

    cout << "Succesful!\n";

    for (int i = 0; i < N ; i++)
        for (int j = 0; j < M; j++)
            cout << outR[i][j] << ( (j < M - 1) ? " " : "\n" );
    
    return 0;
}

unsigned char* ReadBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            // cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
        }
    }

    fclose(f);
    return data;
}

/*void filterRecursive(int lx, int hx, int ly, int hy)
{
    unsigned int sumR = 0, qnt = 0;
    bitset<4> posflag;
    if (lx == hx || ly == hy)
    {
        posflag[0] = lx == N - 1;
        posflag[1] = ly == N - 1;
        posflag[2] = lx == 0;
        posflag[3] = ly == 0;
        switch(stoi(posflag.to_string()))   
        //Da para paralelizar, todas as somas sao independentes
        //#pragma omp parallel reduction(+:sumR)
        {
            case 0011:      //lx == 0 and ly == 0
                sumR += R[lx][ly] * W3;
                sumR += R[lx+1][ly] * W2;
                sumR += R[lx][ly+1] * W2;
                sumR += R[lx+1][ly+1] * W1;
            break;
            case 0010:      //lx == 0
                sumR += R[lx][ly-1] * W2;
                sumR += R[lx+1][ly-1] * W1;
                sumR += R[lx][ly] * W3;
                sumR += R[lx+1][ly] * W1;
                sumR += R[lx][ly+1] * W2;
                sumR += R[lx+1][ly+1] * W1;
            break;
            case 0001:      //ly == 0
                sumR += R[lx-1][ly] * W2;
                sumR += R[lx][ly] * W3;
                sumR += R[lx+1][ly] * W2;
                sumR += R[lx-1][ly+1] * W1;
                sumR += R[lx][ly+1] * W2;
                sumR += R[lx+1][ly+1] * W1;
            break;
            case 1100:      //lx == N and ly == N
                sumR += R[lx-1][ly-1] * W1;
                sumR += R[lx-1][ly] * W2;
                sumR += R[lx][ly-1] * W2;
                sumR += R[lx][ly] * W3;
            break;
            case 1000:      //lx == N
                sumR += R[lx-1][ly-1] * W1;
                sumR += R[lx][ly-1] * W2;
                sumR += R[lx-1][ly] * W2;
                sumR += R[lx][ly] * W3;
                sumR += R[lx-1][ly+1] * W1;
                sumR += R[lx][ly+1] * W2;
            break;
            case 0100:      //ly == N
                sumR += R[lx-1][ly-1] * W1;
                sumR += R[lx][ly-1] * W2;
                sumR += R[lx+1][ly-1] * W1;
                sumR += R[lx-1][ly] * W2;
                sumR += R[lx][ly] * W3;
                sumR += R[lx+1][ly] * W2;
            break;
            default:
                sumR += R[lx-1][ly-1] * W1;
                sumR += R[lx][ly-1] * W2;
                sumR += R[lx+1][ly-1] * W1;
                sumR += R[lx-1][ly] * W2;
                sumR += R[lx][ly] * W3;
                sumR += R[lx+1][ly] * W2;
                sumR += R[lx-1][ly+1] * W1;
                sumR += R[lx][ly+1] * W2;
                sumR += R[lx+1][ly+1] * W1;
            break;
        }

        sumR /= passabaixaTotal;
        
        outR[lx][ly] = sumR;

        return;
    }
    filterRecursive(lx, hx/2, ly, hy/2);
    filterRecursive(hx/2, hx, ly, hy/2);
    filterRecursive(lx, hx/2, hy/2, hy);
    filterRecursive(hx/2, hx, hy/2, hy);
    return;
}
*/

void filterIterative(int lx, int hx, int ly, int hy)
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
        cout << "Ok...\n";
    }

    return;

}