#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define TAM 100000
#define USING_OMP 1

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
    #pragma omp parallel for
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
    #pragma omp parallel for
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2) {
		if (L[i] < R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

        #pragma omp task
		mergeSort(arr, l, m);
        #pragma omp task
		mergeSort(arr, m + 1, r);
        #pragma omp taskwait
		merge(arr, l, m, r);
	}
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int isSorted(int a[], int size)
{
    int i, sorted = 1, aux = a[0];
    for (i = 1; i < size; i++)
        if (aux > a[i])
        {
            sorted = 0;
            break;
        }
    return sorted;
}

/* Driver code */
int main()
{
	int arr[TAM], i;
    #pragma omp parallel for
    for (i = 0; i < TAM; i++)
    {
        arr[i] = TAM - i;
        //printf("%d\n", omp_get_num_threads());
    }
	int arr_size = sizeof(arr) / sizeof(arr[0]);
    double begin, end;
	
    printf("Sorting an array of size %d which contains the sequence from %d to %d\n", TAM, TAM, 1);
    printf("%s OPENMP\n", USING_OMP ? "USING" : "WITHOUT");

    if (TAM < 50)
    {
        printf("Unsorted array:");
        printArray(arr, arr_size);
    }

    begin = omp_get_wtime();
	mergeSort(arr, 0, arr_size - 1);
    end = omp_get_wtime();

    if (TAM < 50)
    {
        printf("Sorted array:");
        printArray(arr, arr_size);
    }

	printf("Sorted array is %s\n", isSorted(arr, arr_size) ? "true" : "false");

    printf("Time elapsed: %.3lfs\n", end - begin);
	return 0;
}
