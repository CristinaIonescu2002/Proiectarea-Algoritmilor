#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int ct, n;
vector<int> DFS;

void dfs(int node, const vector<vector<int>>& adj, vector<int>& vizitat,
                                                        vector<int>& copii) {
    vizitat[node] = 1;
    for (auto& neigh : adj[node]) {
        if (!vizitat[neigh]) {
            DFS.push_back(neigh);
            dfs(neigh, adj, vizitat, copii);
            copii[node] += copii[neigh];
        }
    }
}

int main() {
    FILE* fin = fopen("magazin.in", "r");
    FILE* fout = fopen("magazin.out", "w");

    int m, x, y;
    fscanf(fin, "%d %d", &n, &m);

    vector<vector<int>> adj(n+1);
    vector<int> copii(n+1, 0);
    vector<int> vizitat(n+1, 0);

    for (int i = 2; i <= n; i++) {
        // fin >> x;
        fscanf(fin, "%d", &x);
        adj[x].push_back(i);
        copii[x]++;
    }

    DFS.reserve(n);
    DFS.push_back(1);
    dfs(1, adj, vizitat, copii);

    for (int i=0; i<m; i++) {
        fscanf(fin, "%d %d", &x, &y);

        if (copii[x] < y) {
            fprintf(fout, "-1\n");
        } else if (x == 1) {
            fprintf(fout, "%d\n", DFS[y]);
        } else {
            int j = 0;
            for (j=0; j<DFS.size(); j++) {
                if (DFS[j] == x) {
                    break;
                }
            }
            fprintf(fout, "%d\n", DFS[j + y]);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
