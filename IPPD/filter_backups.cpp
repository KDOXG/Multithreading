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
            case 1100:      //hx == N and hy == N
                sumR += R[hx-1][hy-1] * W1;
                sumR += R[hx-1][hy] * W2;
                sumR += R[hx][hy-1] * W2;
                sumR += R[hx][hy] * W3;
            break;
            case 1000:      //hx == N
                sumR += R[hx-1][hy-1] * W1;
                sumR += R[hx][hy-1] * W2;
                sumR += R[hx-1][hy] * W2;
                sumR += R[hx][hy] * W3;
                sumR += R[hx-1][ly+1] * W1;
                sumR += R[hx][ly+1] * W2;
            break;
            case 0100:      //hy == N
                sumR += R[hx-1][hy-1] * W1;
                sumR += R[hx][hy-1] * W2;
                sumR += R[hx+1][hy-1] * W1;
                sumR += R[hx-1][hy] * W2;
                sumR += R[hx][hy] * W3;
                sumR += R[hx+1][hy] * W2;
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

            
                #pragma omp for
                for (int i = lx; i < lx + 2; i++)
                {
                    #pragma omp for reduction(+:sumR)
                    for (int j = ly; j = ly + 2; j++)
                    {
                        sumR += R[i][j] * passabaixa[i-lx][j-ly];
                    }
                }