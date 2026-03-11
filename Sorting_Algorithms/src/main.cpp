#include <iostream>
#include "include/merge_sort.h"


int main() {

    int tab[10] = {22,3223260,24324,3,356,31,334243,324,324,2342};
    merge_sort(tab,10);
    for(int i = 0 ; i<10;i++) std::cout<<tab[i]<<std::endl;
    return 0;
}