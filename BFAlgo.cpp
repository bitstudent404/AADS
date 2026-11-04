
#include <iostream>
using namespace std;

int main() {
    int V, E;
        cout << "Enter vertices and edges: ";
            cin >> V >> E;

                int u[100], v[100], w[100];
                    int dist[100];

                        cout << "Enter edges (source destination weight):\n";
                            for (int i = 0; i < E; i++) {
                                    cin >> u[i] >> v[i] >> w[i];
                                        }

                                            int source;
                                                cout << "Enter source vertex: ";
                                                    cin >> source;

                                                        // Initialize distances
                                                            for (int i = 0; i < V; i++) {
                                                                    dist[i] = 99999;
                                                                        }

                                                                            dist[source] = 0;

                                                                                // Relax edges V-1 times
                                                                                    for (int i = 1; i < V; i++) {
                                                                                            for (int j = 0; j < E; j++) {
                                                                                                        if (dist[u[j]] != 99999 &&
                                                                                                                        dist[u[j]] + w[j] < dist[v[j]]) {

                                                                                                                                        dist[v[j]] = dist[u[j]] + w[j];
                                                                                                                                                    }
                                                                                                                                                            }
                                                                                                                                                                }

                                                                                                                                                                    // Check negative weight cycle
                                                                                                                                                                        for (int j = 0; j < E; j++) {
                                                                                                                                                                                if (dist[u[j]] != 99999 &&
                                                                                                                                                                                            dist[u[j]] + w[j] < dist[v[j]]) {

                                                                                                                                                                                                        cout << "Negative weight cycle detected!";
                                                                                                                                                                                                                    return 0;
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                    // Print shortest distances
                                                                                                                                                                                                                                        cout << "\nShortest distances:\n";

                                                                                                                                                                                                                                            for (int i = 0; i < V; i++) {
                                                                                                                                                                                                                                                    cout << source << " to " << i << " = ";

                                                                                                                                                                                                                                                            if (dist[i] == 99999)
                                                                                                                                                                                                                                                                        cout << "Unreachable";
                                                                                                                                                                                                                                                                                else
                                                                                                                                                                                                                                                                                            cout << dist[i];

                                                                                                                                                                                                                                                                                                    cout << endl;
                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                            return 0;
                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                            