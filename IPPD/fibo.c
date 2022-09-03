#include <stdio.h>
#include <omp.h>
#define N 5

int fibo1(int n);
int fibo2(int n);

int main()
{
    int r;
    double begin, end;
    begin = omp_get_wtime();
    int n = N;

    #pragma omp parallel shared(n)
    {
    #pragma omp single
    {
        printf("%d\n", omp_get_num_threads());
        r = fibo1(n);
    }
    }

    end = omp_get_wtime();
    printf("OpenMP: With task\n");
    printf("\tFibonacci result for N = %d: %d\n", N, r);
    printf("\tTime elapsed: %.3lfs\n", end - begin);

    begin = omp_get_wtime();

    #pragma omp parallel
    {
    #pragma omp single
    {
        printf("%d\n", omp_get_num_threads());
        r = fibo2(N);
    }
    }

    end = omp_get_wtime();
    printf("OpenMP: With sections\n");
    printf("\tFibonacci result for N = %d: %d\n", N, r);
    printf("\tTime elapsed: %.3lfs\n", end - begin);
    return 0;
}

int fibo1(int n)
{
    int r1, r2;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    #pragma omp task shared(r1) firstprivate(n)
    r1 = fibo1(n-1);

    #pragma omp task shared(r2) firstprivate(n)
    r2 = fibo1(n-2);

    #pragma omp taskwait
    //printf("Current int %d is on thread %d \n", r1 + r2, omp_get_thread_num());
    return r1 + r2;
}

int fibo2(int n)
{
    int r1, r2;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    #pragma omp parallel sections
    {
        #pragma omp section
        {r1 = fibo2(n-1);}
        #pragma omp section
        {r2 = fibo2(n-2);}
    }
    //printf("Current int %d is on thread %d \n", r1 + r2, omp_get_thread_num());
    return r1 + r2;
}