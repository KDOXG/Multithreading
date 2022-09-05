#include "filter.h"

/*
void filterRecursive(int lx, int hx, int ly, int hy)
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