#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <stdexcept>
 
struct Edge {
    int vertex;
    int weight;
};

class Graph {
public:
    explicit Graph(int vertices) : V(vertices) {}
    virtual ~Graph() = default;
 
    virtual void addEdge(int from, int to, int weight) = 0;
    virtual std::vector<Edge> getNeighbors(int v) const = 0;
    int numVertices() const { return V; }
 
protected:
    int V;
};

class AdjacencyList : public Graph {
public:
    explicit AdjacencyList(int vertices)
        : Graph(vertices), adj(vertices) {}
 
    void addEdge(int from, int to, int weight) override {
        if (from < 0 || from >= V || to < 0 || to >= V)
            throw std::out_of_range("Wierzcholek poza zakresem");
        adj[from].push_back({to, weight});
        adj[to].push_back({from, weight}); 
    }
 
    std::vector<Edge> getNeighbors(int v) const override {
        if (v < 0 || v >= V)
            throw std::out_of_range("Wierzcholek poza zakresem");
        return adj[v];
    }
 
private:
    std::vector<std::vector<Edge>> adj;
};

class AdjacencyMatrix : public Graph {
public:
    explicit AdjacencyMatrix(int vertices)
        : Graph(vertices),
          matrix(vertices, std::vector<int>(vertices, 0)) {}
 
    void addEdge(int from, int to, int weight) override {
        if (from < 0 || from >= V || to < 0 || to >= V)
            throw std::out_of_range("Wierzcholek poza zakresem");
        matrix[from][to] = weight;
        matrix[to][from] = weight; 
    }
 
    std::vector<Edge> getNeighbors(int v) const override {
        if (v < 0 || v >= V)
            throw std::out_of_range("Wierzcholek poza zakresem");
        std::vector<Edge> neighbors;
        for (int i = 0; i < V; ++i)
            if (matrix[v][i] != 0)
                neighbors.push_back({i, matrix[v][i]});
        return neighbors;
    }
 
private:
    std::vector<std::vector<int>> matrix;
};