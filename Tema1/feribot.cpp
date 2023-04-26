#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
int n, k;
unsigned long long greutateMaxima;

int verif(unsigned long long v[], unsigned long long greutate) {
    unsigned long long sum2 = 0;
    int ct = 0;
    for (int i = 0; i < n; i++) {
        if (sum2 + v[i] <= greutate) {
            sum2 += v[i];
        } else {
            sum2 = v[i];
            ct++;
        }
    }
    if (sum2 > 0) {
        ct++;
    }
    if (ct > k)
        return 1;
    else if (ct == k)
        return 0;
    return -1;
}

int dividEtImpera(unsigned long long v[], unsigned long st, unsigned long dr) {
    unsigned long mid = (dr + st) / 2;
    if (st <= dr) {
        int flag = verif(v, mid);
        if (flag == -1) {
            greutateMaxima = mid;
            dividEtImpera(v, st, mid - 1);
        } else if (flag == 0) {
            greutateMaxima = mid;
            dividEtImpera(v, st, mid - 1);
        } else if (flag == 1) {
            dividEtImpera(v, mid + 1, dr);
        }
    }
    return -1;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    fin >> n >> k;

    unsigned long long v[n];
    unsigned long long sum = 0;
    unsigned long long max = 0;

    for (int i = 0; i < n ; i++) {
        fin >> v[i];
        if (max < v[i]) {
            max = v[i];
        }
        sum += v[i];
    }

    fout << greutateMaxima;

    dividEtImpera(v, max, sum);
    if (greutateMaxima == 0) {
        greutateMaxima = max;
    }
    fout << greutateMaxima;
}
