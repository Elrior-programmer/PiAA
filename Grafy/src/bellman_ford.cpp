#include "bellman_ford.h"


std::vector<int> bellman_ford(const Graph& g, int src) {
    const int V = g.numVertices();
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(V, INF);
    dist[src] = 0;


    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            if (dist[u] == INF) continue;

            for (const Edge& e : g.getNeighbors(u)) {
                if (dist[u] + e.weight < dist[e.vertex]) {
                    dist[e.vertex] = dist[u] + e.weight;
                }
            }
        }
    }
    return dist;
}