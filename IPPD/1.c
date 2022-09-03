#include <stdio.h>
#include <omp.h>
#define TAM 10

int main()
{
    int vet[TAM], soma = 0, i;
    #pragma omp parallel for
    for (i = 0; i < TAM; i++)
        vet[i] = 5;
    #pragma omp parallel for reduction (+:soma)
    for (i = 0; i < TAM; i++)
    {
        printf("%d\n", omp_get_num_threads());
        soma += vet[i];
    }
    printf("%d\n", soma);
    printf("Sem openmp\n");
    return 0;
}
