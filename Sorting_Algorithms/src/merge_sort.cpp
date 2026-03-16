#include "merge_sort.h"

void merge_sort(int tab[],int size) {
    devide(tab,0,size-1);
}

void devide(int tab[], int left, int right) {
    if(left >= right) return;
    else {
        int middle = left + (right-left)/2;
        devide(tab,left,middle);
        devide(tab,middle+1,right);
        merge(tab,left,middle,right);
    }
}

void merge(int tab[],int left, int middle, int right) {
    
    int left_size = middle - left + 1;
    int right_size = right - middle;
    int left_part[left_size], right_part[right_size];
    for( int i = 0 ; i < left_size ; i++) left_part[i] = tab[left+i];
    for( int i = 0 ; i < right_size ; i++) right_part[i] = tab[middle+i+1];

    int i = 0 , j = 0 , k = left;
    while(i < left_size && j < right_size) {
        if(left_part[i] <= right_part[j]) {
            tab[k] = left_part[i];
            i++;
        }
        else {
            tab[k] = right_part[j];
            j++;
        }
        k++;
    }
    while(i < left_size) {
        tab[k] = left_part[i];
        i++;
        k++;
    }
    while(j < right_size) {
        tab[k] = right_part[j];
        j++;
        k++;
    }

}