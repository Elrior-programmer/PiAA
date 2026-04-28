#include "dijkstra.h"

std::vector<int> dijkstra(const Graph& g, int src) {
    const int V = g.numVertices();
    const int INF = std::numeric_limits<int>::max();
 
    std::vector<int> dist(V, INF);
    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > pq;
 
    dist[src] = 0;
    pq.push({0, src});
 
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
 
        if (d > dist[u]) continue; 
 
        for (const Edge& e : g.getNeighbors(u)) {
            int newDist = dist[u] + e.weight;
            if (newDist < dist[e.to]) {
                dist[e.to] = newDist;
                pq.push({newDist, e.to});
            }
        }
    }
 
    return dist;
}