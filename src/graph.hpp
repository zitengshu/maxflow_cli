#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <vector>
#include <limits>

template<class T>
class Graph{
public:
    explicit Graph(int n);

    void AddLink(int u, int v, T cap);
    auto BFS(int s, int t) -> bool;
    auto DFS(int u, int v, T flow) -> T;
    auto MaxFlow(int s, int t) -> T;

    class Link {
    public:
        explicit Link(T flow, T cap, int v, int rev);

        T flow;  // flow of data in edge
        T cap;   // Capacity of edge
        int v;          // Vertex v(to which the node that the link points)
        int rev;        // Index of reverse link in adjacency list
    };

    auto GetLinks() -> std::vector<std::vector<Link>>&;

private:
    int n;  // number of vertex
    std::vector<int> level;  // level of vertex from source to sink
    std::vector<std::vector<Link>> adj; // Adjecency link list of every vertex 
};

/********** Link ***********/
template<class T>
Graph<T>::Link::Link(T flow, T cap, int v, int rev): flow(flow), cap(cap), v(v), rev(rev) {}

/********** Graph **********/

template<class T>
Graph<T>::Graph(int n) : n(n) {
    level.resize(n);
    adj.resize(n);
}

template<class T>
void Graph<T>::AddLink(int u, int v, T cap) {
    int u_rev = adj[v].size();
    int v_rev = adj[u].size();
    adj[u].emplace_back(static_cast<T>(0), cap, v, u_rev);
    adj[v].emplace_back(static_cast<T>(0), cap, u, v_rev);
}

template<class T>
auto Graph<T>::BFS(int s, int t) -> bool {
    std::fill(level.begin(), level.end(), -1);
    level[s] = 0;
    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &link : adj[u]) {
            int v = link.v;
            if (level[v] < 0 && link.flow < link.cap) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return (level[t] > 0);
}

template<class T>
auto Graph<T>::DFS(int u, int v, T flow) -> T {
    if (u == v) { return flow; }
    int max_link_num = adj[u].size();
    int next_level = level[u] + 1;
    for (auto &link: adj[u]) {
        if (level[link.v] == next_level && link.flow < link.cap) {
            T res_flow = std::min(flow, link.cap - link.flow);
            int max_flow = DFS(link.v, v, res_flow);
            if (max_flow > 0) {
                link.flow += max_flow;
                adj[link.v][link.rev].flow -= max_flow;
                return max_flow;
            }
        }
    }
    return static_cast<T>(0);
}

template<class T>
auto Graph<T>::MaxFlow(int s, int t) -> T {
    if (s == t) { return static_cast<T>(0); }

    T max_flow = static_cast<T>(0);
    while (BFS(s, t)) {
        T flow;
        while ((flow = DFS(s, t, std::numeric_limits<T>::max()))) {
            max_flow += flow;
        }
    }
    return max_flow;
}

template<class T>
auto Graph<T>::GetLinks() -> std::vector<std::vector<Link>>& {
    return adj;
}