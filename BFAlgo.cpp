
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    int V, E;
    cout << "Enter vertices and edges: ";
    cin >> V >> E;

    int u[100], v[100], w[100];
    int dist[100];

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++)
    {
        cin >> u[i] >> v[i] >> w[i];
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    // Initialize distances
    for (int i = 0; i < V; i++)
    {
        dist[i] = 99999;
    }

    dist[source] = 0;

    int relaxations = 0;
    int passes = 0;

    clock_t start = clock();

    // Bellman-Ford: Relax edges V-1 times
    for (int i = 1; i < V; i++)
    {
        passes++;
        int updated = 0;

        for (int j = 0; j < E; j++)
        {
            relaxations++;

            if (dist[u[j]] != 99999 &&
                dist[u[j]] + w[j] < dist[v[j]])
            {
                dist[v[j]] = dist[u[j]] + w[j];
                updated = 1;
            }
        }

        // Stop early if no distance changes
        if (updated == 0)
            break;
    }

    // Check negative weight cycle
    int negativeCycle = 0;

    for (int j = 0; j < E; j++)
    {
        if (dist[u[j]] != 99999 &&
            dist[u[j]] + w[j] < dist[v[j]])
        {
            negativeCycle = 1;
            break;
        }
    }

    clock_t end = clock();

    double timeTaken =
        double(end - start) / CLOCKS_PER_SEC;

    if (negativeCycle)
    {
        cout << "\nNegative weight cycle detected!\n";
    }
    else
    {
        cout << "\nShortest distances:\n";

        for (int i = 0; i < V; i++)
        {
            cout << source << " to " << i << " = ";

            if (dist[i] == 99999)
                cout << "Unreachable";
            else
                cout << dist[i];

            cout << endl;
        }
    }

    cout << "\n--- Performance Analysis ---\n";
    cout << "Number of passes: " << passes << endl;
    cout << "Edge relaxation checks: " << relaxations << endl;
    cout << "Execution time: " << timeTaken
         << " seconds\n";


    return 0;
}
