//*********************************************************************************
//
//  petrel sort_test.cc
//
//  Created by Pingfeng on 04/06/19.
//
//  Description: qsort_implement 
//
//  Usage: ( c++ sort_test.cc -O3 )
//
//*********************************************************************************

#include "sort.h"
#include <cstring>
#include <sys/time.h>

const int RUN_TIMES = 32;
const int SIZE = 10000 * 10;

int verify(SORT_TYPE *dst, const size_t size) {

    for (int i = 1; i < size; i++) {
	if (dst[i - 1] > dst[i]) {
	    printf("SORT IS WRONG\n");
	    return -1;
	}
    }
    return 0;
}

double mtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (1000.0 * t.tv_sec + t.tv_usec/1000.0);
}

void fill(SORT_TYPE *arr, size_t len) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < len; i++) {
	arr[i] = rand() / (float) RAND_MAX;
    }
    return;
}

static __inline int float_cmp(const void *x, const void *y) {
    const SORT_TYPE d_x = *((const SORT_TYPE *) x);
    const SORT_TYPE d_y = *((const SORT_TYPE *) y);
    return (d_x < d_y) ? -1 : (d_x == d_y) ? 0 : 1;
}

int main(int argc, char **argv) {

    SORT_TYPE *arr1  = (SORT_TYPE *) malloc(SIZE * sizeof(SORT_TYPE));
    SORT_TYPE *arr2  = (SORT_TYPE *) malloc(SIZE * sizeof(SORT_TYPE));
    SORT_TYPE *arr3  = (SORT_TYPE *) malloc(SIZE * sizeof(SORT_TYPE));
    SORT_TYPE *arr4  = (SORT_TYPE *) malloc(SIZE * sizeof(SORT_TYPE));

    if (arr1 == NULL || arr2 == NULL || arr3 == NULL || arr4 == NULL) {
	printf("malloc memory error\n");
	exit(1);
    }

    double tot_time = 0.;
    int i = 0;
    fill(arr1, SIZE);

    while (i++ < RUN_TIMES) {
	memcpy(arr2, arr1, sizeof(SORT_TYPE) * SIZE);
	double start = mtime();
	qsort_recursive(arr2, 0, SIZE-1);
	double end = mtime();  
	tot_time += end-start;
    }
    verify(arr2, SIZE);
    printf("qsort_recursive %d elements, average speed is %.4f ms\n", SIZE, tot_time/RUN_TIMES);

    tot_time = 0.;
    i = 0;
    while (i++ < RUN_TIMES) {
	memcpy(arr3, arr1, sizeof(SORT_TYPE) * SIZE);
	double start = mtime();
	qsort_iterative(arr3, 0, SIZE-1);;
	double end = mtime();  
	tot_time += end-start;
    }
    verify(arr3, SIZE);
    printf("qsort_iterative %d elements, average speed is %.4f ms\n", SIZE, tot_time/RUN_TIMES);

    tot_time = 0.;
    i = 0;
    while (i++ < RUN_TIMES) {
	memcpy(arr4, arr1, sizeof(SORT_TYPE) * SIZE);
	double start = mtime();
	qsort(arr4, SIZE, sizeof(SORT_TYPE), float_cmp);
	double end = mtime();  
	tot_time += end-start;
    }
    verify(arr4, SIZE);
    printf("qsort_stdlib    %d elements, average speed is %.4f ms\n", SIZE, tot_time/RUN_TIMES);

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);

    return 0;
}
