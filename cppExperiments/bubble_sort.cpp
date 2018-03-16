#include <iostream>

using namespace std;

int main() {
    const int msize = 10;
    int m[10] = { 1, 0, 2, 9, 3, 8, 4, 7, 5, 6 };

    for (int i = 0; i < msize; i++) {
        cout << m[i];
        if (m[i] > m[i+1]) {
            swap(m[i], m[i+1]);
            cout << endl;
            i = 0;
        }
    }
    cout << endl;
    for (int i = 0; i < msize; i++) {
        cout << m[i];
    }
    return 0;
}
