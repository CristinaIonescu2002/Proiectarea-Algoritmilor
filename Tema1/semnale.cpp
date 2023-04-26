#include <iostream>
#include <vector>

using namespace std;

const int mod = 1000000007;

int triunghiulLuiPascal(int n, int x, int y) {
	vector <vector <long>> A(n+1, vector <long> (n+1, 0));
	for (int i = 0 ; i <=  n; i++) {
        A[i][0] = A[i][i] = 1;
        for (int j = 1 ; j < i ; j ++)
            A[i][j] = (A[i-1][j-1] + A[i-1][j]) % mod;
    }
	return A[x+1][y];
}

int triunghiulLuiPascal2(int x, int y) {
	vector <vector <long>> A(x+1, vector <long> (y+1, 0));
	A[0][0] = 1;
	A[0][1] = 1;
	A[0][2] = 1;
	for(int i = 1 ; i < x+1; i++) {
        A[i][0] = 1;
		A[i][1] = i+1;
        for (int j = 2 ; j < y+1 ; j++) {
			A[i][j] = (A[i-1][j] + A[i-1][j-1] + A[i-1][j-2]) % mod;
		}
    }
	return A[x][y];
}

int type1(int x, int y) {
    // TODO(cristina.ionescu02) Compute the number of type 1 signals.
	if (y > x+1) {
		return 0;
	} else if (y == x+1) {
		return 1;
	}
	return triunghiulLuiPascal(x+y, x, y);
}

int type2(int x, int y) {
    // TODO(cristina.ionescu02) Compute the number of type 2 signals.
	return triunghiulLuiPascal2(x, y);
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
