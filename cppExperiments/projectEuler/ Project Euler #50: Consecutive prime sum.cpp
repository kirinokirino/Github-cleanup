//test cases 2, 7, 8, 9 terminated due to timeout.
//now this requires a lot more of thinking.
//completely copied Miller code, don't know how it works.
//copied sieve code, but changed it a bit and actually know how it works.
//will look int that more, at least to make it nicer, if not to optimize.

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0, y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
bool Miller(ll p, int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2 == 0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

bool isPrime(ull a) {
    if (a == 2) return true;
    if (a % 2 == 0) return false;
    for (ull i = 3; i < a/2+1; i+=2) if (a % i == 0) return false;
    return true;
}

bool primeCheck(bool isComposite[], ull limit, ull a) {
    if (a < 30000000) return !isComposite[a];
    else return Miller(a, 5);
}
/*
    ll upperBound = 2147483647;
    ll primes[400000];
    int upperBoundSquareRoot = (int)sqrt((double)upperBound);
    bool *isComposite = new bool[upperBound + 1];
    memset(isComposite, 0, sizeof(bool) * (upperBound + 1));
    for (int m = 2; m <= upperBoundSquareRoot; m++) {
        if (!isComposite[m]) {
            cout << m << " ";
            for (int k = m * m; k <= upperBound; k += m)
                isComposite[k] = true;
        }
    }
    for (int m = upperBoundSquareRoot; m <= upperBound; m++)
        if (!isComposite[m])
            cout << m << " ";
    delete [] isComposite;
      // - - - - - - - - - - - - - -
      */
/*
vector<int> generatePrimes(ll max) {
    bool isComposite[max+1];
    for (int i = 2; i <= max; i++) {
        isComposite[i] = false;
    }
    for (int i = 2; i * i <= max; i++) {
        if (!isComposite[i]) {
            for (int j = i; i * j <= max; j++) {
                isComposite[i*j] = true;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= max; i++) {
        if (!isComposite[i]) primes.push_back(i);
    }
    return primes;
}
*/

int main() {
    long max = 30000000;
    bool isComposite[max+1];
    for (long i = 2; i <= max; i++) {
        isComposite[i] = false;
    }
    for (long i = 2; i * i <= max; i++) {
        if (!isComposite[i]) {
            for (long j = i; i * j <= max; j++) {
                isComposite[i*j] = true;
            }
        }
    }
    //vector<int> primes = generatePrimes(4000000);
    //cout << "size - " << primes.size() << "\n";
    //for (int i = 0; i < 100; i++) cout << primes[i] << " ";
    
    ull tests = 0;
    cin >> tests;
    for (ull i = 0; i < tests; i++) {
        ull longest_sum = 0, longest_terms = 0;
        ull limit = 0;
        cin >> limit;
        for (ull j = 2; j < 140; j++) {
            ull current_sum = 0, current_terms = 0;
            for (ull k = j; k <= limit; k++) {
                if (primeCheck(isComposite, limit, k)) {
                    current_sum  += k;
                    current_terms++;
                    if (current_sum > limit) {
                        current_sum  -= k;
                        current_terms--;
                        break;
                    }
                    if (primeCheck(isComposite, limit, current_sum)) {
                        if (current_terms > longest_terms) {
                            longest_terms = current_terms;
                            longest_sum = current_sum;
                        }
                    }
                }
            }
            if (primeCheck(isComposite, limit, current_sum)) {
                if (current_terms > longest_terms) {
                    longest_terms = current_terms;
                    longest_sum = current_sum;
                }
            }
        }
        cout << longest_sum << " " << longest_terms << "\n";
    }  
    
    return 0;
}

