#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int rucsac(int n, int W, vector<int> &w, vector<int> &p) {
    vector <vector<int>> dp(n + 1, vector<int>(W+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int cap = 0; cap <= W; cap++) {
            dp[i][cap] = dp[i-1][cap];
            if (cap - w[i] >= 0) {
                int sol_aux = dp[i-1][cap - w[i]] + p[i];
                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }

    return dp[n][W];
}

int Incerc(int n, int W, vector<int> &w, vector<int> &p, int maxim) {
    vector <vector <vector <int>>> dp(n+1,
									vector <vector<int>>(W+1,
												vector<int>(maxim+1, 0)));
	int i;
	int kt = 0;
    for (i = 1; i <= n; i++) {
		if (i <= n/2) {
			kt = i;
		} else {
			kt = i - n/2;
		}
        for (int cap = 0; cap <= W; cap++) {
			for (int j = 1; j <= maxim; j++) {
				dp[i][cap][j] = dp[i-1][cap][j];
				if (cap - w[kt] >= 0) {
					int sol_aux = dp[i-1][cap - w[kt]][j-1] + p[kt];
					dp[i][cap][j] = max(dp[i][cap][j], sol_aux);
				}
			}
        }
		if (dp[i-1][W][maxim] > dp[i][W][maxim]) {
			return dp[i-1][W][maxim];
		}
    }

    return dp[n][W][maxim];
}

int task1(int n, int m, int x, vector <int>& p, vector <vector <int>>& g) {
	// TODO(cristina.ionescu02) solve task 1
	vector <int> rating;
	vector <int> price;
	rating.assign(m+1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			rating[j] += g[i][j];
		}
	}

	int rezultat = rucsac(m, n*x, p, rating);

	return rezultat;
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int>> &g) {
	// TODO(cristina.ionescu02) solve task 2
	vector <int> rating;
	vector <int> price;
	rating.assign((2*m)+1, 0);
	price.assign((2*m)+1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == 1) {
				price[j] = p[j];
				price[j+m] = p[j];
			}
			rating[j] += g[i][j];
			rating[j+m] += g[i][j];
		}
	}

	int rezultat = rucsac(2*m, n*x, price, rating);

	return rezultat;
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int>> &g) {
	// TODO(cristina.ionescu02) solve task 3
	vector <int> rating(m+1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			rating[j] += g[i][j];
		}
	}
	int rezultatInitial = Incerc(2*m, n*x, p, rating, n);

	return rezultatInitial;
}

int main() {
	ifstream fin("sushi.in");
    ofstream fout("sushi.out");

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	fin >> task;
	fin >> n >> m >> x;

	prices.assign(m+1, 0);
	grades.assign(n+1, vector <int> (m+1, 0));

	// price of each sushi
	for(int i = 1; i <= m; ++i) {
		fin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			fin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			fout << "wrong task number" << endl;
	}

	fout << ans << endl;

	return 0;
}
