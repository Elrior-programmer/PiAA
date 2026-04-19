#pragma once
template <typename T>
void quick_sort(T tab[], int left, int right) {

    if(left >= right) return;

    T pivot = tab[(left + right) / 2];
    int i = left;
    int j = right;

    while(i <= j) {

        while(tab[i] < pivot) i++;
        while(tab[j] > pivot) j--;

        if(i <= j) {
            T temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
            i++;
            j--;
        }
    }

    if(left < j) quick_sort(tab, left, j);
    if(i < right) quick_sort(tab, i, right);
}