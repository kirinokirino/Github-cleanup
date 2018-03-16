// test cases 4, 5 are terminated due to timeout.
// everything else is accepted.

using namespace std;

long pow(long a) {
    long res = 1;
        for (long i = 0; i < a; i++) {
            res *= a;
            res %= 10000000000;
        }
        return res;
    }

int main() {
    long N;
    cin >> N;
    long res = 0;
    for (long i = 1; i <= N; i++) {
        res += pow(i%10000000000);
        res %= 10000000000;
    }  
    cout << res << endl;
    return 0;
}
