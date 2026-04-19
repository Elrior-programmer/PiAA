#pragma once
#include "MovieRating.h"
void bucket_sort(MovieRating tab[],int range) {
    int stab[11] = {0};
    int itab[11] = {0};
    for(int i = 0 ; i < range ; i++) {
        stab[tab[i].rating]++;
    }
    MovieRating** buckets = new MovieRating*[10];
    for(int i = 0; i < 11; ++i) {
        buckets[i] = new MovieRating[stab[i]];
    }
    for(int i = 0 ; i < range ; i++) {
        buckets[tab[i].rating][itab[tab[i].rating]] = tab[i];
        itab[tab[i].rating]++;
    }
    int currentPos = 0;
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < stab[i]; ++j) {
            tab[currentPos++] = buckets[i][j];
        }
    }

    for(int i = 0; i < 10; ++i) {
        delete[] buckets[i]; 
    }
    delete[] buckets;
}