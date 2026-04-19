#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <chrono>
#include "MovieRating.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "bucket_sort.h"

int badania(MovieRating tab[], int range);

int main() {
    std::string outFileName = "data/merge_sort_time.csv";
    std::ofstream outFile(outFileName, std::ios::app);
    std::ifstream infile("data/projekt1_dane.csv");
    if(!infile) {
        std::cout << "Blad otwarcia pliku\n";
        return 1;
    }
    int k = 0;
    MovieRating* tab = new MovieRating[962903];
    std::string temp;
    getline(infile,temp);
    for(int i = 0 ; i < 1010294 ; i++) {
        std::string l;
        getline(infile,l);
        if (!l.empty() && l.back() == '\r') {
            l.pop_back();
        }
        std::string temp1 = l.substr(0,l.find(","));
        std::string temp2 = l.substr(l.find(",")+1, l.rfind(",")-l.find(",")-1);
        std::string temp3 ="";
        if(l.rfind(",") == l.size()-1) {
            continue;
        }
        temp3 = l.substr(l.rfind(",")+1,3);
        tab[k] = MovieRating(std::stoi(temp1),temp2,std::stoi(temp3));
        k++;
    }
   
    std::cout<<"Loading Done: "<<k<<"\n";
    for(int i = 0 ; i < 10 ; i++) {
        std::cout<<"Badania do 10 000\n";
        outFile << i << ";" << 10000 << ";" << badania(tab,10000) << "\n";
        std::cout<<"Badania do 100 000\n";
        outFile << i << ";" << 100000 << ";" << badania(tab,100000) << "\n";
        std::cout<<"Badania do 500 000\n";
        outFile << i << ";" << 500000 << ";" << badania(tab,500000) << "\n";
        std::cout<<"Badania do maksymalnego rozmiaru: "<<k<<"\n";
        outFile << i << ";" << k << ";" << badania(tab,k) << "\n";
    }

}

int badania(MovieRating tab[], int range) {
    MovieRating* tab2 = new MovieRating[range];
    for(int i = 0 ; i < range ; i++) {
        tab2[i] = tab[i];
    }
    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(tab2,range);
    auto stop = std::chrono::high_resolution_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    if(std::is_sorted(tab2,tab2+range)) {
        std::cout<<"CORRECT\n";
    }
    else {
        std::cout<<"INCORRECT\n";
    }
    return czas;
}