#include <iostream>
#include <clocale>
#include <math.h>
#include <random>

using namespace std;

void fork0();
void fork1();
void fork2();
void fork3();
void fork11();
void fork12();
void fork13();
void fork14();
void fork15();
void fork16();
void fork21();
void fork22();
void fork23();
void nextGame(); 
bool makeTurn(int low, int high, int target);
bool test(int answer, int target);
bool repeat();

int input(int maximum){
	int ans;
	while (true){
		cout << "Выберите пожалуйста число от 1 до " << maximum << ": ";
		cin >> ans;
		if (ans > maximum) continue;
		else return ans;
	}
}

double input() {
	double a;
	cin >> a;
	return a;
}

void fork11() {

	cout << "Сложение." << endl;
	cout << "Введите, сколько числел хотите сложить." << endl;
	int N = abs(floor(input()));
	double sum = 0;
	for (int i = 0; i < N; i++) {
		cout << "Введите " << i + 1 << " число." << endl;
		sum += input();
	}
	cout << "Сумма равна " << sum << endl;
}

void fork12() {

	cout << "Вычетание." << endl;

	double raz = 0;
	cout << "Введите число, из которого хотите вычесть." << endl;
	raz = input();

	cout << "Введите, сколько числел хотите вычесть." << endl;
	int N = abs(floor(input()));
	for (int i = 0; i < N; i++) {
		cout << "Введите " << i + 1 << " число." << endl;
		raz -= input();
	}
	cout << "Разница равна " << raz << endl;
}

void fork13() {

	cout << "Произведение." << endl;
	cout << "Введите, сколько числел хотите умножить." << endl;
	int N = abs(floor(input()));
	double proizv = 1;
	for (int i = 0; i < N; i++) {
		cout << "Введите " << i + 1 << " число." << endl;
		proizv *= input();
	}
	cout << "Сумма равна " << proizv << endl;
}

void fork14() {

	cout << "Деление." << endl;

	double del = 0;
	cout << "Введите число, которое хотите поделить." << endl;
	del = input();

	cout << "Введите, на сколько числел хотите поделить." << endl;
	int N = abs(floor(input()));

	for (int i = 0; i < N; i++) {
		cout << "Введите " << i + 1 << " число." << endl;
		del /= input();
	}
	cout << "Сумма равна " << del << endl;
}

void fork15() {

	cout << "Возведение в степень." << endl;

	double first = 0, second = 0;
	cout << "Введите число, которое хотите возвести в степень." << endl;
	first = input();

	cout << "Введите степень." << endl;
	second = input();

	cout << "Возведенное в степень число равно " << pow(first, second) << endl;

}

void fork16() {

	cout << "Вычислить корень." << endl;

	double root = 0;
	cout << "Введите число, из которого хотите вычислить квадратный корень." << endl;
	root = input();

	cout << "Корень равен " << sqrt(root) << endl;

}

void fork1() {

	cout << "1. Сложить." << endl;
	cout << "2. Вычесть." << endl;
	cout << "3. Умножить." << endl;
	cout << "4. Поделить." << endl;
	cout << "5. Возвести в степень." << endl;
	cout << "6. Вычислить корень." << endl;
	cout << "7. Назад." << endl;

	int ans = input(7);
	if (ans == 1) fork11();
	else if (ans == 2) fork12();
	else if (ans == 3) fork13();
	else if (ans == 4) fork14();
	else if (ans == 5) fork15();
	else if (ans == 6) fork16();
	else if (ans == 7) fork0();
}

// Вычисление площади кольца. // ---
void fork21() {

	double R1, R2, PI = 3.14;
	cout << "Вычисление площади кольца." << endl;

	// Ввод переменных с проверками
	while (true) {
		cout << "Введите радиус внутренней окружности: ";
		R1 = input();
		cout << "Введите радиус внешней окружности: ";
		R2 = input();

		// Проверки
		if (R1 == R2) cout << "Радиусы не должны совпадать." << endl; // Проверка на совпадение.
		else if (R1 < R2) break; // Если внутренний радиус меньше внешнего, то проверка пройдена.
		else cout << "Внутренняя окружность должна быть меньше внешней" << endl; // В остальных случаях - нет.
	}

	// Вывод и вычисление площади кольца
	cout << "Радиус полученного кольца = " << PI*R2*R2 - PI*R1*R1 << endl;
}

// Нахождение корней квадратного уравнения. // ---
void fork22() {

	double a, b, c, D;
	cout << "Нахождение корней квадратного уравнения ax^2+bx+c=0." << endl;

	// Ввод переменных с проверками.
	while (true) {
		cout << "Введите а: ";
		a = input();
		if (a == 0) { // По условию a != 0
			cout << "Переменная a не должна быть равна 0" << endl;
			continue; // Если проверка не пройдена, пропускает последующие действия и просит ввести а вновь.
		}
		// На b и c нет ограничений.
		cout << "Введите b: ";
		b = input();
		cout << "Введите c: ";
		c = input();

		D = b*b - 4 * a*c; // Вычисление дискриминанта, можно было использовать возведение в квадрат из библиотеки math.h.
		if (D < 0) cout << "Дискриминант не должен быть меньше нуля, нет решений." << endl;
		else break; // Если дискриминант меньше нуля, цикл повторится, иначе - ввод переменных успешно завершится.
	}

	// Вывод и вычисление.
	cout << "D = " << D << endl; // Не обязательно выводить дискриминант.
	if (D == 0) cout << "x1, x2 = " << -b / 2 * a; // Разделение на квадратные уравнения с одним или двумя корнями.
	else {
		cout << "x1 = " << (-b + sqrt(D)) / 2 * a << endl;
		cout << "x2 = " << (-b - sqrt(D)) / 2 * a << endl;
	}

}

// Нахождение решения системы уравнений // ---
void fork23() {

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
}

void fork2() {

	cout << "1. Площадь кольца." << endl;
	cout << "2. Корни квадратного уравнения." << endl;
	cout << "3. Решение системы уравнений." << endl;
	cout << "4. Назад." << endl;
	int ans = input(4);
	if (ans == 1) fork21();
	else if (ans == 2) fork22();
	else if (ans == 3) fork23();
	else if (ans == 4) fork0();
}

void fork3() {

	cout << "Игра \"угадай число!\"" << endl;
	// Объявление переменных для нижней и верхней границ случайных чисел, для счетчика ходов.
	int low, high, turn = 0;
	// Запрос границ случайных чисел.
	cout << "Введите нижнюю границу загадываемых чисел" << endl;
	cin >> low;
	cout << "Введите верхнюю границу загадываемых чисел" << endl;
	cin >> high;

	// Генератор случайных чисел и допустимые случайные значения.
	uniform_int_distribution<> distribution(low, high); // Все случайные числа будут от low до high.
	mt19937 gen; // Самый обширно используемый генератор случайных чисел.
	gen.seed(std::random_device()()); // Для того, чтобы при каждом запуске были разные последовательности чисел. 

	int target = distribution(gen); // Компьютер "загадывает" число в заданных рамках.
	cout << "Число загадано, попытайтесь его угадать!" << endl;

	// Цикл обработки хода, большая часть работы перенесена в функцию makeTurn().
	do {
		cout << "Попытка номер " << ++turn << endl;
	} while (!makeTurn(low, high, target));

	// Конец игры - вывод намера хода и лушего гарантированного времени.
	cout << "Вы угадали с " << turn << " попытки!" << endl;
	cout << "Минимальное время гарантированного нахождения числа - " << ceil(log(high - low)) << endl;
	nextGame();
}

// Предложение сыграть ещё.
void nextGame(){

	char answer = 'q'; // Использование символа вместо чего-то ещё не имеет значения, мне больше нравится y/n.
	while (true) {
		cout << "Хотите ли вы сыграть ещё раз? (y/n): ";
		cin >> answer;
		if (answer == 'y' || answer == 'n') break; // Если не была введена ни n, ни y - просьба повторить ввод.
		else cout << "Команда некорректна, попытайтесь ещё раз." << endl;
	}
	// Если был введен символ y, повторно вызываем функцию основного цикла игры. 
	if (answer == 'n') {
		cout << "Выход из игры" << endl;
	}
	else fork3();
}

// Функция обработки попытки угадать число.
bool makeTurn(int low, int high, int target){
	int answer = 0;
	while (true) { // Нельзя попытаться угадать число больше или меньше заданных границ.
		cin >> answer;
		if (answer > high || answer < low) cout << "Недопустимое значение, попытайтесь ещё раз." << endl;
		else break;
	}
	return test(answer, target); // Проверка верности вынесена в отдельную функцию.
}

// Проверка, было ли угадано число.
bool test(int answer, int target){
	// Выводит, больше или меньше попытка угадать число чем цель.
	if (answer > target) {
		cout << "Загаданное число меньше." << endl;
		return false;
	}
	else if (answer < target) {
		cout << "Загаданное число больше." << endl;
		return false;
	}
	else return true; // Возвращает true только если число было угадано.
}

void fork0() {
	cout << "1. Простейшие действия." << endl;
	cout << "2. Решение задач." << endl;
	cout << "3. Игра \"Угадай число\"." << endl;
	cout << "4. Выход." << endl;
	int ans = input(4);
	if (ans == 1) fork1();
	else if (ans == 2) fork2();
	else if (ans == 3) fork3();
}

bool repeat() {
	char answer = 'q'; // Использование символа вместо чего-то ещё не имеет значения, мне больше нравится y/n.
	while (true) {
		cout << "Хотите ли вы продолжить? (y/n): ";
		cin >> answer;
		if (answer == 'y' || answer == 'n') break; // Если не была введена ни n, ни y - просьба повторить ввод.
		else cout << "Команда некорректна, попытайтесь ещё раз." << endl;
	}
	// Если был введен символ y, повторно вызываем функцию основного цикла игры. 
	if (answer == 'n') {
		cout << "Выход." << endl;
		return false;
	}
	else return true;
}

int main() {
	setlocale(LC_ALL, "rus");

	while (true) {
		fork0();
		if (!repeat()) break;
	}

	system("PAUSE");
	return 0;
}
