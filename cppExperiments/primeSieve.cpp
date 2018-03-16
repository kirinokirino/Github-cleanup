using namespace std;

int main() {
    
    const int max = 4000000;
    bool isPrime[max];
    for (int i = 0; i < max; i++) {
        isPrime[i] = true;
    }
    for (int i = 2; i*i < max; i++) {
        if(isPrime[i]) {
            for (int j = 2; i*j < max; j++) {
                isPrime[i*j] = false;
            }
        } 
    }
    
    for (int i = 2; i < 100; i++) {
        if (isPrime[i] == true) cout << i << " ";
    }
    return 0;
}
