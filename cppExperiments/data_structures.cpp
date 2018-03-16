#include <iostream>
#include <bitset>

using namespace std;

union mix_t {
        int l;
        struct {
                short hi;
                short lo;
        } s;
        char c[4];
};

// Not possible with old enum's
// enum colors_t;
// void colorFunction(colors_t a);

enum class colors_new;
void colorFunction2(colors_new a);

enum colors_t {black, blue, green, cyan, red, purple, yellow, white};
enum class colors_new {black, blue, green, cyan, red, purple, yellow, white};

int main() {
        mix_t mix;
        cout << "sizeof int: " << sizeof(mix.l) << endl;
        cout << "sizeof short: " << sizeof(mix.s.hi) << endl;
        cout << "sizeof char: " << sizeof(mix.c[0]) << endl;
        cout << "sizeof union (of these ^): " << sizeof(mix) << endl;
        cout << endl;

        colors_t color = white;
        cout << "sizeof colors_t: " << sizeof(colors_t) << endl;
        cout << "color: " << color << endl;
        if (color == white) cout << "color is white!" << endl;
        cout << endl;

        colors_new color_new = colors_new::white;
        cout << "sizeof colors_new: " << sizeof(colors_new) << endl;
        cout << "color_new is not a number, actually" << endl;
        cout << "color_new's size is " << sizeof(color_new) << endl;
        if (color_new == colors_new::white) {
            cout << "color_new is white! (c++11 and not global)" << endl;
            cout << endl;
        }

        typedef unsigned short ushort2;
        using ushort = unsigned short;
        cout << "sizeof ushort: " << sizeof(ushort) << endl;
        cout << "sizeof ushort2: " << sizeof(ushort2) << endl;
        cout << "They are the same" << endl;
        cout << endl;

        struct y{
            unsigned first : 1;
            unsigned second : 1;
            unsigned third : 1;
        }y;
        y.first = 0;
        y.second = 1;
        y.third = 0;
        cout << "bitfield: " << y.first << y.second << y.third << endl;

        bitset<3> x;
        x[1] = 1;
        x[2] = 0;
        cout << "bitset: " << x << endl;

        return 0;
}
