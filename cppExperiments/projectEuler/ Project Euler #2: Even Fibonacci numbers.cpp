// accepted.

#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        ull n;
        cin >> n;
        
        vector<ull> fibSequence;
        fibSequence.emplace_back(1);
        fibSequence.emplace_back(2);
        ull before_last = 1;
        ull sum = 0;
        while (fibSequence.back() < n) {
            ull temp = before_last + fibSequence.back();
            before_last = fibSequence.back();
            if (before_last % 2 == 0) sum += before_last;
            fibSequence.emplace_back(temp);
        }
        cout << sum << "\n";
    }
    return 0;
}
