#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> topsort1;
vector<int> topsort2;

// de retinut algoritmul de sortare topologica a fost luat din labul 7
void dfs(int node, vector<int>& used, vector<int>& tasks,
                                            vector<vector<int>>& adj, int n) {
    used[node] = 1;
    for (auto& neigh : adj[node]) {
        if (!used[neigh]) {
            dfs(neigh, used, tasks, adj, n);
        }
    }

    if (tasks[node] == 1) {
        topsort1.push_back(node);
    } else {
        topsort2.push_back(node);
    }
}

int main() {
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");
    int n, m, x, y;
    fin >> n >> m;

    vector<int> tasks(n+1);
    vector<int> parinti(n+1, 0);
    vector<vector<int>> adj(n+1);

    tasks[0] = 0;
    for (int i = 1; i <= n; i++) {
        fin >> tasks[i];
    }

    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        adj[x].push_back(y);
        parinti[y]++;
    }

    vector<int> used(n + 1, 0);

    for (int node = 1; node <= n; ++node) {
        if (!used[node]) {
            dfs(node, used,  tasks, adj, n);
        }
    }

    int pas = 0;
    int urm = 0;
    int urm2 = 0;
    int ct = 0;
    int ct2 = 0;
    int i = topsort1.size() - 1;
    int j = topsort2.size() - 1;
    int ok = 0;
    queue<int> q;
    vector<int> modif(n+1, 0);


    while (i > -1 && j > -1) {
        int t1 = 0;
        int t2 = 0;

        while (i > -1 && (parinti[topsort1[i]] == 0 ||
                                                parinti[topsort1[i]] == -1)) {
            for (int w = 0; w < adj[topsort1[i]].size(); w++) {
                q.push(adj[topsort1[i]][w]);
                parinti[adj[topsort1[i]][w]]--;
                modif[adj[topsort1[i]][w]] = 1;

                if (parinti[adj[topsort1[i]][w]] == 0) {
                    parinti[adj[topsort1[i]][w]] = -1;
                }
            }
            t1 = 1;
            i--;
        }
        while (j > -1 && (parinti[topsort2[j]] == 0
                                        || parinti[topsort2[j]] == -2)) {
            for (int w = 0; w<adj[topsort2[j]].size(); w++) {
                q.push(adj[topsort2[j]][w]);
                parinti[adj[topsort2[j]][w]]--;
                if (parinti[adj[topsort2[j]][w]] == 0) {
                    if (modif[adj[topsort2[j]][w]] == 1) {
                        parinti[adj[topsort2[j]][w]] = -1;
                    } else {
                        parinti[adj[topsort2[j]][w]] = -2;
                    }
                }
            }
            t2 = 1;
            j--;
        }
        while (q.size() > 0) {
            int nr = q.front();

            if (parinti[nr] == -1 || parinti[nr] == -2) {
                parinti[nr] = 0;
                modif[nr] = 0;
            }

            q.pop();
        }

        if (pas == 0) {
            if (t1 == 1 && t2 == 1) {
                ok = 1;
                urm = 2;
                urm2 = 1;
                ct++;
                ct2++;
            } else if (t2 == 1) {
                urm = 2;
                urm2 = 2;
            } else {
                urm = 1;
                urm2 = 1;
            }
            pas++;
        } else {
            if (t1 == 1 && t2 == 1) {
                if (urm == 1) {
                    urm = 2;
                } else if (urm == 2) {
                    urm = 1;
                }
                if (urm2 == 1) {
                    urm2 = 2;
                } else if (urm2 == 2) {
                    urm2 = 1;
                }
                ct++;
                ct2++;
            } else if (t2 == 1 && t1 == 0) {
                if (urm == 1) {
                    ct++;
                    urm = 2;
                }
                if (urm2 == 1) {
                    ct2++;
                    urm2 = 2;
                }
            } else if (t1 == 1 && t2 == 0) {
                if (urm == 2) {
                    ct++;
                    urm = 1;
                }
                if (urm2 == 2) {
                    ct2++;
                    urm2 = 1;
                }
            }
        }
    }

    if (j > -1 && urm == 1) {
        ct++;
    } else if (i > -1 && urm == 2) {
        ct++;
    }

    if (j > -1 && urm2 == 1) {
        ct2++;
    } else if (i > -1 && urm2 == 2) {
        ct2++;
    }

    fout << min(ct, ct2);

    fin.close();
    return 0;
}
