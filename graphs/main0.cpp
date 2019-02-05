#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>

void explore_and_remove(std::unordered_map<int, std::unordered_set<int>>& g,
                        int u,
                        std::unordered_set<int>& visited) {
    // if this is a leaf
    // remove the node from the graph
    auto& neighbors = g[u];
    if (neighbors.size() == 1) {
        // find the corresponding edge for the other end
        auto const& v = g.find(*neighbors.begin());
        // erase u from edge set from v
        g[v->first].erase(u);
        // remove u
        g.erase(u);
        return;
    }

    // reach only if u is not a leaf
    visited.insert(u);
    // for each unvisited edge from u -> v, traverse and check v node
    for (auto const& v : neighbors) {
        if (visited.find(v) == visited.end())
            explore_and_remove(g, v, visited);
    }
}

void iterate(std::unordered_map<int, std::unordered_set<int>>& g) {
    std::unordered_set<int> visited;
    for (auto const& p : g) {
        if (visited.find(p.first) == visited.end())
            explore_and_remove(g, p.first, visited);
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
        std::cout << "size = " << g.size() << std::endl;
        iterate(g);
    }

    for (auto const& p : g) {
        std::cout << p.first << " ";
    }
    std::cout << std::endl;

    return 0;
}
