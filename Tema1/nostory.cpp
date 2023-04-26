/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */
#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

int64_t SolveTask1(vector<int>& a, vector<int>& b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());

    int64_t sum = 0;
    int lungime = a.size();

    for (int i = 0; i < lungime; i++) {
        sum += max(a[i], b[i]);
    }

    return sum;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int moves) {
    int lungime = a.size();
    long sum = 0;

    vector <int> minV(lungime, 0);
    vector <int> maxV(lungime, 0);

    for (int i = 0; i < lungime; i++) {
        minV[i] = min(a[i], b[i]);
        maxV[i] = max(a[i], b[i]);
        sum += maxV[i];
    }

    sort(minV.begin(), minV.end(), greater<int>());
    sort(maxV.begin(), maxV.end());

    int i = 0;

    while (moves > 0) {
        if (minV[i] < maxV[i])
            break;
        sum = sum - maxV[i] + minV[i];
        i++;
        moves--;
    }

    return sum;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
