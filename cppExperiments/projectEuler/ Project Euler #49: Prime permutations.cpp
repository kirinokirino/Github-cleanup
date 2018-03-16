// test cases 3, 4, 6 (of 6) terminated due to timeout.
// didn't used any help yet, quite happy with this tbh.

using namespace std;

int getDigits(int num) {
    if      ((num / 100000) % 10 != 0) return 6;
    else if ((num / 10000 ) % 10 != 0) return 5;
    else if ((num / 1000  ) % 10 != 0) return 4;
    else return 0;
}

int getDigit(int num, int pos) {
    return (num / (int)pow(10, pos)) % 10;
}

void checkAnswer(vector<int> digits) {
     /*
    if (digits[0] == 1487) {
    for (int i = 0; i < digits.size(); i++) {
        cout << digits[i] << " ";
    }
    cout << " -- ";
    }
    // */
    
    int nums[10];
    for (int i = 0; i < 10; i++) {
        nums[i] = 0;
    }
    for (int i = 0; i < digits.size(); i++) {
        int numsTemp[10];
        for (int i = 0; i < 10; i++) {
            numsTemp[i] = 0;
        }
        for (int j = 0; j < getDigits(digits[i]); j++) {
            // if (digits[0] == 1487) cout << getDigit(digits[i], j) << " ";
            numsTemp[getDigit(digits[i], j)]++;
        }
        // if (digits[0] == 1487) cout << "\n";
        if (i != 0) {
            for (int j = 0; j < 10; j++) {
                if (nums[j] != numsTemp[j]) return;
                        // if (digits[0] == 1487) cout << nums[j] << "_" << numsTemp[j] << " ";
            }
        } else {
            for (int j = 0; j < 10; j++) {
                nums[j] = numsTemp[j];
                        // if (digits[0] == 1487) cout << nums[j] << "_" << numsTemp[j] << " ";
            }
        }
    }
    for (int i = 0; i < digits.size(); i++) {
        cout << digits[i];
    }
    cout << endl;
}

void tryProgression(int first, int second, const bool isComposite[]) {
    int delta = second - first;
    if (!isComposite[second+delta] && !isComposite[second+delta*2]) {
        // cout << first << " + " << delta << " = " << second << "\n";
        // if (first == 1487) cout << first << " + " << delta << " = " << second << "\n";
        vector<int> digits;
        digits.push_back(first);
        digits.push_back(second);
        digits.push_back(second+delta);
        digits.push_back(second+delta*2);
        checkAnswer(digits);
    }
}

void tryProgression3(int first, int second, const bool isComposite[]) {
    int delta = second - first;
    if (!isComposite[second+delta]) {
        // cout << first << " + " << delta << " = " << second << "\n";
        // if (first == 1487) cout << first << " + " << delta << " = " << second << "\n";
        vector<int> digits;
        digits.push_back(first);
        digits.push_back(second);
        digits.push_back(second+delta);
        checkAnswer(digits);
    }
}

void findFirstTwo(int whichCase, int N, int K, const bool isComposite[]) {
    // cout << "case " << whichCase << ":\n";
    int limit = 1;
    for (int i = 0; i < whichCase; i++) limit *= 10;
    for (int i = limit/10; i < N; i++) {
        if (!isComposite[i]) {
            for (int j = i+1; j < limit; j++) {
                if (!isComposite[j]) {
                    // if (i == 1487) cout << i << " - " << j << "  |  ";
                    // cout << i << " - " << j << "  |  ";
                    if (K == 3) tryProgression3(i, j, isComposite);
                    else        tryProgression(i, j, isComposite);
                }
            }
        }
    }
}

int main() {
    long max = 4000000;
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
    int N = 0, K = 0;
    cin >> N >> K;
    /* switch (getDigits(N)) {
        case 4:
            findFirstTwo(4, N, K, isComposite);
        case 5:
            findFirstTwo(5, N, K, isComposite);
        case 6:
            findFirstTwo(6, N, K, isComposite);
            break;
    } */
            findFirstTwo(4, N, K, isComposite);
            findFirstTwo(5, N, K, isComposite);
            findFirstTwo(6, N, K, isComposite);
    return 0;
}
