#include <iostream>
using std::cout;
using std::endl;

struct pair {
        int first;
        int second;
};

void print(struct pair a);
pair add(pair a, pair b);
pair sub(pair a, pair b);
pair mul(pair a, pair b);
pair div(pair a, pair b);
int NOD(int a, int b);
int NOK(int a, int b);

int main() {
        pair a; a.first = 2; a.second = 5;
        pair b; b.first = 7; b.second = 3;
        print(add(a,b));
        print(sub(a,b));
        print(mul(a,b));
        print(div(a,b));
}

void print(pair a) {
        cout << " " << a.first << endl;
        cout << "-----" << endl;
        cout << " " << a.second << endl;
}

pair add(pair a, pair b) {
        int UP = a.first*b.second + b.first*a.second;
        int DOWN = a.second*b.second;
        pair result; result.first = UP/NOD(UP, DOWN); result.second = DOWN/NOD(UP, DOWN);
        return result;
}

pair sub(pair a, pair b) {
        int UP = a.first*b.second - b.first*a.second;
        int DOWN = a.second*b.second;
        pair result; result.first = UP/NOD(UP, DOWN); result.second = DOWN/NOD(UP, DOWN);
        return result;
}

pair mul(pair a, pair b) {
        int UP = a.first*b.first;
        int DOWN = a.second*b.second;
        pair result; result.first = UP/NOD(UP, DOWN); result.second = DOWN/NOD(UP, DOWN);
        return result;
}

pair div(pair a, pair b) {
        int UP = a.first*b.second;
        int DOWN = a.second*b.first;
        pair result; result.first = UP/NOD(UP, DOWN); result.second = DOWN/NOD(UP, DOWN);
        return result;
}

int NOD(int a, int b) {
        // return b ? gcd (b, a % b) : a;
        if (a == 0) return 99999;
        if (b == 0)
                return a;
        else
                return NOD(b, a%b);
}

int NOK(int a, int b) {
        return a / NOD(a, b)*b;
}
