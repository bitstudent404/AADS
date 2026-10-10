#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

int parent[100];

int find(int v) {
    if (parent[v] == v)
        return v;
    return parent[v] = find(parent[v]);
}

void unite(int u, int v) {
    parent[find(u)] = find(v);
}

int main() {
    int n, e;
    Edge edges[100];

    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    cout << "Enter source, destination and weight of each edge:\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    sort(edges, edges + e, [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    for (int i = 0; i < n; i++)
        parent[i] = i;

    int totalWeight = 0, count = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (int i = 0; i < e && count < n - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (find(u) != find(v)) {
            cout << u << " - " << v
                 << " : " << edges[i].weight << endl;

            unite(u, v);
            totalWeight += edges[i].weight;
            count++;
        }
    }

    if (count != n - 1)
        cout << "MST does not exist. Graph is disconnected.\n";
    else
        cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}