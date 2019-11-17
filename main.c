#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include <omp.h>
#include <math.h>

#define COUNT 300
#define LOWER 1
#define UPPER 99

struct matrix {
    int a[COUNT];
};

struct sorting_stats {
    char *name;
    double time;
};

/*
void pigeonholeSort(int *a, int n)
{
    int i;
    int min = a[0], max = a[0];
    for (i = 1; i < n; i++)
    {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }

    int size, count = 0;
    size = max - min + 1;
    int holes[size];
    int *current;
    current = a;

    for (i = 0; i < size; i++)
        holes[i] = 0;

    for (i = 0; i < size; i++, current++)
        holes[*current - min]++;

    for (count = 0, current = &a[0]; count < size; count++)
        while (holes[count]-- > 0)
            *current++ = count + min;
}
*/


void pigeonholeSort(int *a, int n)
{
    int i;
    int min = a[0], max = a[0];
    for (i=0; i<n; i++)
    {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    int range = max - min + 1;
    int holes[range];
    for (i = 0; i < range; i++)
        holes[i] = 0;

    for (i=0; i<n; i++)
        holes[a[i]-min]++;

    int index = 0;
    for (i=0; i < range; i++)
        while (holes[i]-- > 0)
        {
            a[index++] = i + min;
        }
}

void pigeonholeSortTimeComplexity(int *a, int n)
{
    int i;
    int min = a[0], max = a[0];
    for (i=0; i<n; i++)
    {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    int range = max - min + 1;
    printf("Time complexity: %lf\n", log2(range + n));
}

// A utility function to get maximum value in arr[]
int getMax(int *a, int n)
{
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int *arr, int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = {0};

    //printf("Store count of occurrences in count[] \n");
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (long i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (long i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixSort(int *a, int n)
{
    // Find the maximum number to know number of digits
    const int m = getMax(a, n);

    int exp;
    for (exp = 1; m/exp > 0; exp *= 10) {
        countSort(a, n, exp);
    }
}

void radixSortTimeComplexity(int *a, int n)
{
    const int m = getMax(a, n);

    int exp;
    for (exp = 1; m/exp > 0; exp *= 10);
    printf("Time complexity: %lf\n", log2(exp * n));
}











void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int choose_pivot(int i,int j )
{
    return((i+j) /2);
}

void quicksort(int *list,int m,int n)
{
    int key,i,j,k;
    if( m < n)
    {
        k = choose_pivot(m,n);
        swap(&list[m],&list[k]);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if( i < j)
                swap(&list[i],&list[j]);
        }
        /* swap two elements */
        swap(&list[m],&list[j]);

        /* recursively sort the lesser list */
        quicksort(list,m,j-1);
        quicksort(list,j+1,n);
    }
}











void printArray(int *a, int n)
{
    printf("Size: %d\n", n);
    for (int i=0; i<n; i++)
        printf("%2d ", a[i]);
    printf("\n");
}

void printMatrix(struct matrix *a, int n)
{
    printf("Size: %d x %d\n", n, n);
    for (int i=0; i<n; i++)
    {
        for (int j=0;  j<n; j++)
            printf("%2d ", a[i].a[j]);
        printf("\n");
    }
    printf("\n");
}

int compare (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main()
{
    double startCalc, endCalc;
    double runTime;
    struct sorting_stats sorting_stats[4] = {{NULL,0}};
    int sortAlgoCount=0;

    int array[COUNT];
    int n = sizeof(array)/sizeof(array[0]);
    struct matrix m_pigeon[COUNT];
    struct matrix m_quicks[COUNT];
    struct matrix m_quicksort[COUNT];
    struct matrix m_radixs[COUNT];

    int a_pigeon[COUNT];
    int a_quicks[COUNT];
    int a_quicksort[COUNT];
    int a_radixs[COUNT];

    //for (int i=0; i<n; i++)
        //array[i] = (rand() % (UPPER - LOWER + 1)) + LOWER;

for (int k=0; k<COUNT*20; k++)
{
    sortAlgoCount = 0;
    for (int i=0; i<COUNT; i++)
        //for (int j=0;  j<n; j++)
            //m_pigeon[i].a[j] = m_quicks[i].a[j] = m_radixs[i].a[j] = m_quicksort[i].a[j] =
            a_pigeon[i] = a_quicks[i] = a_quicksort[i] = a_radixs[i] =
                    (rand() % (UPPER - LOWER + 1)) + LOWER;

    //printArray(array, n);
    //printMatrix(m_quicksort, n);

    /*
    startCalc = omp_get_wtime();
    pigeonholeSort(array, n);
    endCalc = omp_get_wtime();
    runTime = endCalc - startCalc;
    printf("\npigeonholeSort %d elements in \t%f seconds\n\n",COUNT,runTime);
    */

    startCalc = omp_get_wtime();
    //for (int i=0; i<COUNT; i++)
        //pigeonholeSort(m_pigeon[i].a, n);
        pigeonholeSort(a_pigeon, n);
    endCalc = omp_get_wtime();
    runTime = endCalc - startCalc;
    //pigeonholeSortTimeComplexity(m_pigeon[0].a,n);
    //printf("%15s %dx%d elements in %10.15f ms\n\n","pigeonholeSort",COUNT,COUNT,runTime*1000);
    sorting_stats[sortAlgoCount  ].name = "pigeonholeSort";
    sorting_stats[sortAlgoCount++].time += runTime*1000;

    startCalc = omp_get_wtime();
    //for (int i=0; i<COUNT; i++)
        //radixSort(m_radixs[i].a, n);
        radixSort(a_radixs, n);
    endCalc = omp_get_wtime();
    runTime = endCalc - startCalc;
    //radixSortTimeComplexity(m_radixs[0].a, n);
    //printf("%15s %dx%d elements in %10.15f ms\n\n","radixSort",COUNT,COUNT,runTime*1000);
    sorting_stats[sortAlgoCount  ].name = "radixSort";
    sorting_stats[sortAlgoCount++].time += runTime*1000;

    startCalc = omp_get_wtime();
    //for (int i=0; i<COUNT; i++)
        //qsort(m_quicks[i].a, n, sizeof(int), compare);
        qsort(a_quicks, n, sizeof(int), compare);
    endCalc = omp_get_wtime();
    runTime = endCalc - startCalc;
    //printf("Time complexity: %lf\n", n * log2(n));
    //printf("%15s %dx%d elements in %10.15f ms\n\n","qsort",COUNT,COUNT,runTime*1000);
    sorting_stats[sortAlgoCount  ].name = "qsort";
    sorting_stats[sortAlgoCount++].time += runTime*1000;

    startCalc = omp_get_wtime();
    //for (int i=0; i<COUNT; i++)
        //quicksort(m_quicksort[i].a, 0, n-1);
        quicksort(a_quicksort, 0, n-1);
    endCalc = omp_get_wtime();
    runTime = endCalc - startCalc;
    //printf("Time complexity: %lf\n", n * log2(n));
    //printf("%15s %dx%d elements in %10.15f ms\n\n","quicksort",COUNT,COUNT,runTime*1000);
    sorting_stats[sortAlgoCount  ].name = "quicksort";
    sorting_stats[sortAlgoCount++].time += runTime*1000;
}

    for (int i=0; i<sortAlgoCount-1; i++)
    {
        if (sorting_stats[i].time > sorting_stats[i+1].time)
        {
            struct sorting_stats tmp;
            tmp = sorting_stats[i];
            sorting_stats[i] = sorting_stats[i+1];
            sorting_stats[i+1] = tmp;
            i=-1;
        }
    }

    for (int i=0; i<sortAlgoCount; i++)
    {
        printf("%15s : %10.15f\n", sorting_stats[i].name, sorting_stats[i].time);
    }

    //printMatrix(m_quicksort, n);
    //printf("Sorted array:\n");
    //printArray(array, n);

    //printf("Sorted matrix:\n");
    //printMatrix(m, n);

    return 0;
}
