#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <numeric>
#include <chrono>
#include "dijkstra.h"
#include "bellman_ford.h"

void generateGraph(Graph& g, int vertices, int densityPercent) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> weightDist(1, 100);
    std::uniform_int_distribution<int> chanceDist(1, 100);

    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            if (chanceDist(rng) <= densityPercent) {
                g.addEdge(i, j, weightDist(rng));
            }
        }
    }
}

int main() {
    int vertiecies_count[5] = { 10, 50, 100, 500, 1000};
    int percent[4] = { 25, 50, 75, 100 };
    std::string graph_type[2] = { "list", "matrix"};
        for(int g_t = 0 ; g_t < 2 ; g_t++) {
            for(int i = 0 ; i < 5 ; i++) {
                for(int j = 0 ; j < 4 ; j++) {
                    std::string File1 = "data/" + std::to_string(vertiecies_count[i]) + '_' + std::to_string(percent[j]) + '_' + "dijkstra" +'_' + graph_type[g_t] + ".csv";
                    std::string File2 = "data/" + std::to_string(vertiecies_count[i]) + '_' + std::to_string(percent[j]) + '_' + "bellman_ford" +'_' + graph_type[g_t] + ".csv";
                    if (std::filesystem::exists(File1) && std::filesystem::exists(File2)) {
                        std::cout << "Juz policzyles\n";
                        continue;
                    }
                    else {
                        std::ofstream f1(File1);
                        std::ofstream f2(File2);
                        f1 << "run,ns\n";
                        f2 << "run,ns\n";
                        for(int k = 0 ; k < 100 ; k++) {
                            Graph* g;
                            if (graph_type[g_t] == "list") g = new AdjacencyList(vertiecies_count[i]);
                            else g = new AdjacencyMatrix(vertiecies_count[i]);

                            generateGraph(*g,vertiecies_count[i],percent[j]);
                            
                            auto start = std::chrono::steady_clock::now();
                            dijkstra(*g, 0);
                            auto stop = std::chrono::steady_clock::now();
                            long long t_d = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
                            
                            start = std::chrono::steady_clock::now();
                            bellman_ford(*g, 0);
                            stop = std::chrono::steady_clock::now();
                            long long t_b = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
                            delete g;

                            f1 << k << ',' << t_d << '\n';
                            f2 << k << ',' << t_b << '\n';

                        }
                    }
                }
            }
        }
    return 0; 
}

