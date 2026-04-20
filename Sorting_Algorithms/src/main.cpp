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

struct wyniki
{
    long long czas;
    int mean;
    float avg;

    wyniki(long long c, int m, float a) : czas{c}, mean{m}, avg{a} {}

    wyniki& operator=(const wyniki& other) {
        this->czas = other.czas;
        this->mean = other.mean;
        this->avg = other.avg;
        return *this;
    }
};


wyniki badania(MovieRating tab[], int range);

float avg(MovieRating tab[], int range) {
    float sum = 0;
    for(int i =  0 ; i < range ; i++) {
        sum += tab[i].rating;
    }
    return (float)(sum/(float)range);
}

int mean(MovieRating tab[], int range) {
    int numbers[11] = {0};
    for(int i = 0 ; i < range ; i++) {
        numbers[tab[i].rating]++;
    }
    int max_ = 0;
    int max_num = 0;

    for(int i = 0 ; i < 11 ; i++) {
        if(numbers[i]>max_) {
            max_ = numbers[i];
            max_num = i;
        }
    }
    return max_num;
}

int main() {
    std::string outFileName = "data/quick_sort_time.csv";
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
        wyniki w1 = badania(tab,10000);
        outFile << i << ";" << 10000 << ";" << w1.czas << ";" << w1.avg << ";" << w1.mean << "\n";
        std::cout<<"Badania do 100 000\n";
        w1 = badania(tab,100000);
        outFile << i << ";" << 100000 << ";" << w1.czas << ";" << w1.avg << ";" << w1.mean << "\n";
        std::cout<<"Badania do 500 000\n";
        w1 = badania(tab,500000);
        outFile << i << ";" << 500000 << ";" << w1.czas << ";" << w1.avg << ";" << w1.mean << "\n";
        std::cout<<"Badania do maksymalnego rozmiaru: "<<k<<"\n";
        w1 = badania(tab,k);
        outFile << i << ";" << k << ";" << w1.czas << ";" << w1.avg << ";" << w1.mean << "\n";
    }
}

wyniki badania(MovieRating tab[], int range) {
    MovieRating* tab2 = new MovieRating[range];
    for(int i = 0 ; i < range ; i++) {
        tab2[i] = tab[i];
    }
    auto start = std::chrono::steady_clock::now();
    quick_sort(tab2,0,range);
    auto stop = std::chrono::steady_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    float meanl = mean(tab2,range);
    float avgl = avg(tab2,range);
    if(std::is_sorted(tab2,tab2+range)) {
        std::cout<<"CORRECT\n";
    }
    else {
        std::cout<<"INCORRECT\n";
    }
    return wyniki(czas,meanl,avgl);
}