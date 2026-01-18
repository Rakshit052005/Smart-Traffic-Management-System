#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 1000;

// Graph: adjacency list {neighbor, travel time}
vector<pair<int,int>> adj[MAX_NODES];

// Dijkstra's algorithm to find shortest paths
void dijkstra(int src, int n, vector<int>& dist, vector<int>& parent) {
    dist.assign(n+1, INT_MAX);
    parent.assign(n+1, -1);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});

    while(!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if(d > dist[u]) continue; // ignore outdated entry

        for(auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Print path from source to destination
void printPath(int dest, vector<int>& parent) {
    if(dest == -1) return;
    printPath(parent[dest], parent);
    if(parent[dest] != -1) cout << " -> ";
    cout << dest;
}

// Update traffic (change weight of a road)
void updateTraffic(int u, int v, int newWeight) {
    for(auto &edge : adj[u]) {
        if(edge.first == v) edge.second = newWeight;
    }
    for(auto &edge : adj[v]) {
        if(edge.first == u) edge.second = newWeight;
    }
}

int main() {
    int n = 5; 
    int m = 6; 

    vector<tuple<int,int,int>> edges = {
        {1, 2, 4},
        {1, 3, 2},
        {2, 3, 5},
        {2, 4, 10},
        {3, 5, 3},
        {4, 5, 1}
    };

    for(auto e : edges){
        int u, v, w;
        tie(u, v, w) = e;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); 
    }

    int src = 1;  
    int dest = 4; 

    vector<int> dist, parent;

    cout << "==== Smart Traffic Management System ====\n";
    cout << "Initial shortest path:\n";

    dijkstra(src, n, dist, parent);
    cout << "Shortest distance from " << src << " to " << dest << ": " << dist[dest] << endl;
    cout << "Path: ";
    printPath(dest, parent);
    cout << endl;

    cout << "\nSimulating traffic congestion on road 3-5 (increasing weight from 3 to 10)...\n";
    updateTraffic(3, 5, 10);

    dijkstra(src, n, dist, parent);
    cout << "After traffic update, shortest distance from " << src << " to " << dest << ": " << dist[dest] << endl;
    cout << "Path: ";
    printPath(dest, parent);
    cout << endl;

    return 0;
}
