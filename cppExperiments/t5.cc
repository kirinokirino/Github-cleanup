#include <iostream>
// Библиотека по работе с (псевдо-)случайными числами.
#include <random>
// Здесь используется для нахождения логарифма и округления вверх. (log(), ceil()).
#include <math.h>

using namespace std;

// Раннее объявление описаных позднее функций.
void gameLoop();
void nextGame();
bool makeTurn(int low, int high, int target);
bool test(int answer, int target);

int main(){
        gameLoop();
        return 0;
}

void gameLoop(){

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
	} while(!makeTurn(low, high, target));

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
        } else gameLoop();
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
	} else if (answer < target) {
		cout << "Загаданное число больше." << endl;
		return false;
	} else return true; // Возвращает true только если число было угадано.
}
