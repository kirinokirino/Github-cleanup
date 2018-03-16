// accepted

using namespace std;

typedef unsigned long long ul;

ul sumThrees(ul to) {
	return (to+1) * to * 3 / 2;
}

ul sumFives(ul to) {
	return (to+1) * to * 5 / 2;
}

ul sumFifteens(ul to) {
	return (to+1) * to * 15 / 2;
}

ul findSum(ul to) {
	return sumThrees((to-1)/3) + sumFives((to-1)/5) - sumFifteens((to-1)/15);
}

int main() {
	ul tests = 0, n = 0;
	cin >> tests;
	for (ul i = 0; i < tests; i++) {
		cin >> n;
		cout << findSum(n) << "\n";
	}
	return 0;
}
