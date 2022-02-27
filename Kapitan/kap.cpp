#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

#define INF 2147483647

/*
 * We initially store information about the islands using the Island structure.
 * Then we build graph, with edges corresponding to the distance through which
 * the captain will lead the ship, calculated using sorting (we are only
 * interested in sailing to the nearest islands - separately along the Ox axis
 * and the Oy axis). After receiving the optimized graph, the shortestPath
 * function, using Dijkstra's algorithm finds the shortest path from the island
 * with id 1, to the last given in the task.
 */

struct Island {
    int x;
    int y;
    int id;
};

class Graph {
    int V;
    
    vector<pair<int, int>> *adj;
    
public:
    Graph(int V);

    void addEdge(int u, int v, int w);

    void shortestPath(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<pair<int, int>>[V];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src) {
    priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq;

    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        vector< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    printf("%d\n", dist[V - 1]);
}

int absoluteValue(int x) {
    if (x < 0)
        return -x;
    return x;
}

/* Distance the captain will have to steer the ship, between two isles */
int captainLength(Island a, Island b) {
    int A = absoluteValue(a.x - b.x), B = absoluteValue (a.y - b.y);
    return min(A, B);
}

/* Sort by x coordinate */
bool islandSortX(Island a, Island b) {
    if (a.x >= b.x)
        return false;
    return true;
}

/* Sort by y coordinate */
bool islandSortY(Island a, Island b) {
    if (a.y >= b.y)
        return false;
    return true;
}


int main()
{
    int n;
    int xi, yi, distance;

    scanf("%d", &n);

    Island archipelago[n + 1];
    Graph g(n + 1);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &xi);
        scanf("%d", &yi);

        archipelago[i].id = i;
        archipelago[i].x = xi;
        archipelago[i].y = yi;
    }

    sort(archipelago + 1, archipelago + n + 1, islandSortX);

    for (int i = 1; i < n; ++i) {
        distance = captainLength(archipelago[i], archipelago[i + 1]);
        g.addEdge(archipelago[i].id, archipelago[i + 1].id, distance);
    }

     sort(archipelago + 1, archipelago + n + 1, islandSortY);

    for (int i = 1; i < n; ++i) {
        distance = captainLength(archipelago[i], archipelago[i + 1]);
        g.addEdge(archipelago[i].id, archipelago[i + 1].id, distance);
    }

    g.shortestPath(1);
    return 0;
}
