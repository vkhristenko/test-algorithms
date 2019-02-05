#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>

void print_graph(std::unordered_map<int, std::unordered_set<int>>& g) {
    for (auto const& p : g) {
        std::cout << "vertex: " << p.first << " -> ";
        for (auto const& v : p.second) 
            std::cout << v << " ";
        std::cout << std::endl;
    }
}

void explore_and_remove(std::unordered_map<int, std::unordered_set<int>>& g,
                        int u,
                        std::unordered_set<int>& visited,
                        std::unordered_map<int, int>& nedges_removed) {
    // if u is a leaf
    // remove the node from the graph
    auto& neighbors = g[u];
    std::cout << "u = " << u << std::endl;
    if (neighbors.size() == 1 && nedges_removed.find(u) == nedges_removed.end()) {
        std::cout << "\tu = " << u << std::endl;
        // find the corresponding edge for the other end
        auto const& v = g.find(*neighbors.begin());
        // erase u from edge set from v
        g[v->first].erase(u);
        if (nedges_removed.find(v->first) == nedges_removed.end())
            nedges_removed[v->first] = 0;
        else
            nedges_removed[v->first]++;
        // remove u
        g.erase(u);
        return;
    }

    // reach only if u is not a leaf
    visited.insert(u);
    // for each unvisited edge from u -> v, traverse and check v node
    for (auto& v : neighbors) {
        if (visited.find(v) == visited.end()) {
            std::cout << v << std::endl;
            explore_and_remove(g, v, visited, nedges_removed);
        }
    }
}

void iterate(std::unordered_map<int, std::unordered_set<int>>& g) {
    std::unordered_set<int> visited;
    std::unordered_map<int, int> nedges_removed;
    std::cout << "graph size = " << g.size() << std::endl;
    for (auto& p : g) {
        std::cout << p.first << std::endl;
        print_graph(g);
        if (visited.find(p.first) == visited.end()) {
            std::cout << p.first << std::endl;
            explore_and_remove(g, p.first, visited, nedges_removed);
        }
    }
}

int main() {
    int V, E;
    std::cin >> V >> E;
    std::unordered_map<int, std::unordered_set<int>> g;
    for (int i=0; i<E; i++) {
        int u, v;
        std::cin >> u >> v;
        if (g.find(u) != g.end()) {
            g[u].insert(v);
        } else {
            g[u] = {v};
        }

        if (g.find(v) != g.end()) {
            g[v].insert(v);
        } else {
            g[v] = {u};
        }
    }

    while (g.size() > 2) {
        std::cout << "\t\t\t next iteration\n";
        iterate(g);
    }

    print_graph(g);

    for (auto const& p : g) {
        std::cout << p.first << " ";
    }
    std::cout << std::endl;

    return 0;
}
