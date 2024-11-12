#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <iostream>
using namespace std;

ifstream fin("teleportare.in");
ofstream fout("teleportare.out");

typedef struct nodes {
    int dest;
    int cost;
    int timp;
} node;

class Graph {
    int n;
    list<node> *adjList;
 public:
    Graph() {
       n = 0;
    }

    explicit Graph(int nodeCount) {
       n = nodeCount;
       adjList = new list<node>[n];
    }

    void addEdge(int source, int dest, int cost, int timp) {
       node newNode;
       newNode.dest = dest;
       newNode.cost = cost;
       newNode.timp = timp;
       adjList[source].push_back(newNode);
    }

    friend void dijkstra(Graph g, int start);
};

void dijkstra(Graph g, int start) {
    int n = g.n;
    vector <int> dist(n+1, 999999);
    vector <int> dist2[n+1];
    vector <int> prev(n+1, -1);

    dist[start] = 0;
    set<int> S;
    list<int> Q;

    for (int u = 0; u<n; u++) {
       Q.push_back(u);
    }

    vector <int> timpi[n+1];
    timpi[1].push_back(0);
    dist2[1].push_back(0);

    while (!Q.empty()) {
       list<int> :: iterator i;
       i = min_element(Q.begin(), Q.end());
       int u = *i;
       Q.remove(u);
       S.insert(u);
       list<node> :: iterator it;

       for (it = g.adjList[u].begin(); it != g.adjList[u].end(); it++) {
          if ((dist[u]+(it->cost)) <= dist[it->dest]) {
             for (int w = 0; w < dist2[u].size(); w++) {
                dist2[it->dest].push_back(dist2[u][w]+(it->cost));
             }
             for (int w = 0; w < timpi[u].size(); w++) {
                timpi[it->dest].push_back(timpi[u][w] + 1);
             }

             int ok = 0;

             if (it->timp != 0) {
                for (int w = 0; w < timpi[it->dest].size(); w++) {
                   if (timpi[it->dest][w] % it->timp == 0 &&
                                                timpi[it->dest][w] != -1) {
                      dist[it->dest] = (dist[u]+(it->cost));
                      prev[it->dest] = u;
                      ok = 1;
                   } else {
                      if (w == timpi[it->dest].size() - 1 && ok != 1) {
                         timpi[it->dest][w] = -1;
                      } else {
                         dist2[it->dest][w] = dist2[it->dest][w] -
                                                      (it->cost) + (it->timp);
                      }
                   }
                }
             } else if (it->timp == 0) {
                dist[it->dest] = (dist[u]+(it->cost));
                prev[it->dest] = u;
             }
          }
       }
    }
    int min = INFINITY;
    for (int w = 0; w<timpi[n].size(); w++) {
       if (timpi[n][w] != -1 && min > dist2[n][w]) {
          min = dist2[n][w];
       }
    }
    fout<<min;
}

int main() {
    int n, m, s, x, y, t;

    fin >> n >> m >> s;
    Graph g(n);

    for (int i = 0; i < m; i++) {
       fin>>x>>y>>t;
       g.addEdge(x, y, t, 0);
    }
    for (int i = 0; i < s; i++) {
       fin>>x>>y>>t;
       g.addEdge(x, y, 1, t);
    }
    dijkstra(g, 1);

    fin.close();
    return 0;
}
