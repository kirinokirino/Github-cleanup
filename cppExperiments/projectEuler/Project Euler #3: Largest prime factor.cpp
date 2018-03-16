#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int main() {
    
    const ull max = 1000000;
    bool isPrime[max+1];
    for (ull i = 2; i < max; i++) {
        isPrime[i] = true;
    }
    for (ull i = 2; i*i < max; i++) {
        if(isPrime[i]) {
            for (ull j = 2; i*j < max; j++) {
                isPrime[i*j] = false;
            }
        } 
    }
    
    int tests = 0;
    cin >> tests;
    for (int test = 0; test < tests; test++) {
        ull n = 0;
        cin >> n;
        ull maxDiv = 1;
        
        for (ull i = 2; i*i <= n; i++) {
            if (isPrime[i] && n % i == 0) {
                n /= i;
                maxDiv = i;
                i--;
            } 
        }
        if (n > maxDiv) cout << n << "\n";
        else cout << maxDiv << "\n";
    }
    return 0;
}
