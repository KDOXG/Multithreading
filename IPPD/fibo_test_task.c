#include <stdio.h>
#include <omp.h>

int fib(int n)
{
    int r1, r2;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    #pragma omp task shared(r1) firstprivate(n)
    r1 = fib(n-1);

    #pragma omp task shared(r2) firstprivate(n)
    r2 = fib(n-2);

    #pragma omp taskwait
    printf("Current int %d is on thread %d \n", r1 + r2, omp_get_thread_num());
    return r1 + r2;
}

int main()
{
    int r;
    double begin, end;
    begin = omp_get_wtime();
    int n = 5;

    #pragma omp parallel shared(n)
    {
    #pragma omp single
    {
        printf("%d\n", omp_get_num_threads());
        r = fib(n);
    }
    }

    end = omp_get_wtime();
    printf("OpenMP: With task\n");
    printf("\tFibonacci result for N = %d: %i\n", n, r);
    printf("\tTime elapsed: %.3lfs\n", end - begin);

    #pragma omp parallel shared(n)
    {
    #pragma omp single
    {
        printf("%d\n", omp_get_num_threads());
        printf("fib(%d) = %d\n", n, fib(n));
    }
    }
}