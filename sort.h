//*********************************************************************************
//
//  petrel sort.h
//
//  Created by Pingfeng on 04/06/19.
//
//  Description: 
//
//*********************************************************************************
#ifndef SORT_H_
#define SORT_H_
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>

#define SORT_TYPE float
#ifndef SORT_TYPE
#error "data type for sort is not declare"
#endif

inline int sort_cmp(const SORT_TYPE &x, const SORT_TYPE &y) {
    return x < y ? -1 : (x == y ? 0 : 1);
}

inline void sort_swap(SORT_TYPE *x, SORT_TYPE *y) {
    SORT_TYPE t = *x;
    *x = *y;
    *y = t;
}

inline size_t binary_search_find(SORT_TYPE *src, SORT_TYPE x, int len) {
    register int l = 0;
    register int r = len - 1;

    while (l <= r) {
	int m = (l + r)>>1;

	if (src[m] == x)
	    return m;

	if (src[m] < x)
	    l = m + 1;
	else
	    r = m - 1;
    }

    return -1;
}

void isort(SORT_TYPE *src, size_t len) {
    if (len <= 1 || src == NULL) {
	return;
    }

    for (int i = 0; i < len; i++) {
	SORT_TYPE x = src[i];
	int loc = binary_search_find(src, x, i+1);
	assert(loc != -1);
	int j = i;
	while (j >= loc) {
	    src[j+1] = src[j];
	    j--;
	}
	src[loc] = x;
    }

    return;
}

inline size_t qsort_partition(SORT_TYPE src[], const size_t l, const size_t r) {
    size_t p_index = l;
    int is_same = 0;
    SORT_TYPE p = src[r];

    for (int j = l; j < r; j++) {
	int cmp = sort_cmp(src[j], p); 
	is_same |= cmp;
	if (cmp < 0) {
	    sort_swap(&src[p_index], &src[j]);
	    p_index++;
	}
    }
    if (!is_same)
	return -1;

    sort_swap(&src[p_index], &src[r]);
    return p_index;
}

inline void qsort_recursive(SORT_TYPE *src, const int l, const int r) {
    if (l < r) {
	int p = qsort_partition(src, l, r);
	if (p == -1)
	    return;

	qsort_recursive(src, l, p-1);
	qsort_recursive(src, p+1, r);
    }
}

void qsort_iterative(SORT_TYPE * src, int l, int r) {
    int * stack = (int *) malloc(sizeof(int) * (r-l+1));
    assert(stack != NULL);

    int top = -1;
    stack[++top] = l;
    stack[++top] = r;

    while (top >= 0) {
	r = stack[top--];
	l = stack[top--];

	int p = qsort_partition(src, l, r);
	if (p == -1)
	    continue;

	if (p-1 > l) {
	    stack[++top] = l;
	    stack[++top] = p - 1;
	}

	if (p+1 < r) {
	    stack[++top] = p + 1;
	    stack[++top] = r;
	}
    }

    free(stack);
}

void qsort(SORT_TYPE *src, int len) {
    if (len <= 1 || src == NULL) {
	return;
    }

    qsort_recursive(src, 0, len-1);
}

#endif
