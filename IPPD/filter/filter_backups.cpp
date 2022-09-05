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


    
    
    ifstream *imagem = new ifstream(argv[1], ios::binary);
    
    vector<char> *bytes = new vector<char>(
            (istreambuf_iterator<char>(*imagem)),
            (istreambuf_iterator<char>()));

    string *bytes = new string((char*)ReadBMP(argv[1]));

    imagem->close();

    cout << bytes->size() << endl << 1920*3 << endl << 1280*3 << endl;

    delete(bytes);

    

    //filterRecursive(0, N, 0, M);
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


    const int n = fileInfo->pBMPInfoHeader->biWidth;
    const int m = fileInfo->pBMPInfoHeader->biHeight;

    unsigned short int R[n][m], G[n][m], B[n][m];
    unsigned short int outR[n][m], outG[n][m], outB[n][m];

    vector<vector<uint16_t>> R(n,vector<uint16_t>(m)), G(n,vector<uint16_t>(m)), B(n,vector<uint16_t>(m));
    vector<vector<uint16_t>> outR(n,vector<uint16_t>(m)), outG(n,vector<uint16_t>(m)), outB(n,vector<uint16_t>(m));


    // filterIterative(img);