#include <bits/stdc++.h>
using namespace std;

ifstream fin("ferate.in");
ofstream fout("ferate.out");

void SCCUtil(vector<int> adj[], int n, int u, int disc[], int low[],
                        stack<int>* st, bool stackMember[], int source,
                        int &ct, vector<int>& gradIntern) {
	static int time = 0;

	disc[u] = low[u] = ++time;
	st->push(u);
	stackMember[u] = true;

	for (int i = 0; i < adj[u].size(); ++i) {
		if (disc[adj[u][i]] == -1) {
			SCCUtil(adj, n, adj[u][i], disc, low, st, stackMember, source,
                                                        ct, gradIntern);
			low[u] = min(low[u], low[adj[u][i]]);
		} else if (stackMember[adj[u][i]] == true) {
            low[u] = min(low[u], disc[adj[u][i]]);
        }
	}

	int w = 0;
    int nrGrade = 0;
    int nr = 0;
    int ok = 0;

	if (low[u] == disc[u]) {
		while (st->top() != u) {
			w = (int)st->top();

            if (w == source)
                ok = 1;

            nrGrade += gradIntern[w];
            nr++;
			stackMember[w] = false;
			st->pop();
		}
		w = (int)st->top();

        if (w == source)
            ok = 1;

        nrGrade += gradIntern[w];
        nr++;
		stackMember[w] = false;
		st->pop();

        if (nr == 1 && nrGrade == 0 && ok == 0) {
            ct++;
        } else if (nr > 1 && nrGrade == nr && ok == 0) {
            ct++;
        }
	}
}

void SCC(vector <int> adj[], int n, int source, vector<int>& gradIntern) {
	int* disc = new int[n+1];
	int* low = new int[n+1];
	bool* stackMember = new bool[n+1];
	stack<int>* st = new stack<int>();
    vector<int> sccSol;
    int ct = 0;

	for (int i = 1; i <= n; i++) {
		disc[i] = -1;
		low[i] = -1;
		stackMember[i] = false;
	}

	for (int i = 1; i <= n; i++)
		if (disc[i] == -1) {
            SCCUtil(adj, n, i, disc, low, st, stackMember, source, ct,
                                                                gradIntern);
        }
    fout << ct;
}

int main() {
    int n, m, s, x, y;
    fin >> n >> m >> s;

    vector<int> adj[n+1];
    vector<int> gradIntern(n+1);

    for (int i = 1; i <= m; i++) {
        fin >> x >> y;
        adj[x].push_back(y);
        gradIntern[y]++;
    }

    SCC(adj, n, s, gradIntern);

    fin.close();
    return 0;
}
