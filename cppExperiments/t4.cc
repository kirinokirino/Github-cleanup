#include <iostream> 
#include <clocale>

using namespace std;

// Ввод числа.
double input() {
	double a;
	cin >> a;
	return a;
}

int main() {
	setlocale(LC_ALL, "rus");

	double a1, a2, b1, b2, c1, c2;
	cout << "Нахождение решения системы уравнений\n a1x + b1y = c1\n a2x + b2y = c2" << endl;

	// Ввод переменных с проверками на совпадения.
	while (true) {
		cout << "Введите а1: ";
		a1 = input();
		cout << "Введите a2, не равную а1: ";
		a2 = input();
		if (a2 == a1) continue; // Возвращается в начало цикла если проверка не пройдена.
		cout << "Введите b1: ";
		b1 = input();
		cout << "Введите b2, не равную b1: ";
		b2 = input();
		if (b2 == b1) continue;
		cout << "Введите c1: ";
		c1 = input();
		cout << "Введите c2, не равную c1: ";
		c2 = input();
		if (c2 == c1) continue;

		break;
	}

	// Вывод и вычисление корней системы уравниний.
	cout << "x = " << (c1*b2 - c2*b1) / (a1*b2 - b1*a2) << endl;
	cout << "y = " << (c2*a1 - c1*a2) / (a1*b2 - b1*a2) << endl;

	system("PAUSE");
	return 0;
}
