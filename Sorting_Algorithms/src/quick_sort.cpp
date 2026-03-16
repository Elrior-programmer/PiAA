#include "quick_sort.h"

void quick_sort(int tab[], int size) {

    if(size <= 1) return;

    int pivot = tab[size-1];

    int l_size = 0, e_size = 1, r_size = 0;

    for(int i = 0; i < size-1; i++) {
        if(tab[i] < pivot) l_size++;
        else if(tab[i] == pivot) e_size++;
        else r_size++;
    }

    int* left = new int[l_size];
    int* equal = new int[e_size];
    int* right = new int[r_size];

    int li = 0, ei = 0, ri = 0;

    for(int i = 0; i < size-1; i++) {
        if(tab[i] < pivot)
            left[li++] = tab[i];
        else if(tab[i] == pivot)
            equal[ei++] = tab[i];
        else
            right[ri++] = tab[i];
    }

    equal[ei] = pivot;

    quick_sort(left, l_size);
    quick_sort(right, r_size);

    for(int i = 0; i < l_size; i++)
        tab[i] = left[i];

    for(int i = 0; i < e_size; i++)
        tab[l_size + i] = equal[i];

    for(int i = 0; i < r_size; i++)
        tab[l_size + e_size + i] = right[i];

    delete[] left;
    delete[] equal;
    delete[] right;
}


void quick_sort2(int tab[], int left, int right) {

    if(left >= right) return;

    int pivot = tab[(left + right) / 2];
    int i = left;
    int j = right;

    while(i <= j) {

        while(tab[i] < pivot) i++;
        while(tab[j] > pivot) j--;

        if(i <= j) {
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
            i++;
            j--;
        }
    }

    if(left < j) quick_sort2(tab, left, j);
    if(i < right) quick_sort2(tab, i, right);
}