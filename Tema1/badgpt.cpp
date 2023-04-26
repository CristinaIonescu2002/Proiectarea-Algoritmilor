#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

const int mod = 1000000007;

long fib(unsigned long n) {
    long a = 1;
    long b = 1;
    if (n <= 1)
        return 1;
    for (unsigned long i = 2; i <= n; i++) {
        long c = (a + b) % mod;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    freopen("badgpt.in", "r", stdin);
	freopen("badgpt.out", "w", stdout);

    char litera;
    unsigned long nr;
    unsigned long solutii = 1;
    // int i=0;

    while (cin >> litera >> nr) {
        // cout<<"litera "<<litera<<" nr "<<nr<<"\n";
        if (litera == 'n' || litera == 'u') {
            // cout<< i <<" fib "<< fib(nr)<<endl;
            solutii = (solutii * fib(nr)) % mod;
        }
        // i++;
    }

    cout << solutii << endl;

    return 0;
}
