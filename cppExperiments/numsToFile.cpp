#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

string genNumber();

random_device rd;
mt19937 rnd(rd());
uniform_int_distribution<int> distribution(1,99);

int main() {
	
	ofstream out;
	out.open("data.txt", ofstream::out);
	out << "Here's some random numbers for you!" << endl;
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			out << genNumber() << " ";
		}
		out << endl;
	}
	return 0;
}

string genNumber() {
	int num = distribution(rnd);
	if (num < 10) return "0" + to_string(num);
	else return to_string(num);
}
