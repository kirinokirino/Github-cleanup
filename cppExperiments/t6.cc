/* Единственное задание, в котором имеет хоть малейший смысл использовать C++, а не C */

#include <iostream>
#include <vector>
#include <string>
#include <clocale>

using namespace std;

// Создание класса группы. Можно так же использовать отдельные функции для обработки вектора, не объединяя их в класс.
class Group {
public:
	Group(){}; // Конструктор.
	virtual ~Group(){}; // Деструктор.

	// Ввод студентов в экземпляр группы.
	void fill() {
		string student;
		while (true) {
			cout << "Введите имя студента. Если хотите завершить ввод, введите 0." << endl;
			cin >> student;
			if (student == "0") break; // Завершение ввода если был введен 0.
			else addStudent(student); // Добавление студента в экземпляр группы.
		}
	}

	// Функция получения групп дежурных.
	void divide(int subGroups) {
		cout << "Выбран каждый " << subGroups << endl;
		for (int i = 0; i < subGroups; i++) {
			cout << "Группа дежурных номер " << i + 1 << endl;
			for (int j = i; j < countStudents(); j += subGroups) {
				cout << "   " << getStudent(j) << endl;
			}
		}
	}
	// Добавление студента в группу.
	void addStudent(string student){ students.emplace_back(student); };
	// Получение имени студента.
	string getStudent(int id){ return students[id]; };
private: // Все что не используется вне экземпляра класса.
	// Получение количества студентов в группе.
	int countStudents(){ return students.size(); };
	vector<string> students; // Вектор строк - имен студентов.
};

// Запрос на составление группы дежурных.
int ask() {
	cout << "Выбор каждого X человека из группы в качестве дежурного." << endl;
	cout << "Введите Х: ";
	int X;
	cin >> X;
	return X;
}

int main() {
	setlocale(LC_ALL, "rus");

	// Создаем пустую группу студентов.
	Group myGroup;

	// Заполняем группу, затем получаем из неё 
	myGroup.fill();
	myGroup.divide(ask());

	system("PAUSE");
	return 0;
}

