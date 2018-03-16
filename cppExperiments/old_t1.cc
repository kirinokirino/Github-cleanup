/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2017 kirinokirino <kirinokirino2501@yahoo.com>
 * 
 * exam is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * exam is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <algorithm> 
#include <math.h> 

using std::cout;
using std::endl;
using std::string;
using std::remove_if;
using std::distance;

double to_double(string number);
double compute(double first, double second, char operation);
string collapse(string expression);
string ordering(string expression);

int main()
{
	//string test = "52+42+(53-(34+4)-5) + 3-5-(53+42)";
	//cout << ordering(test);
	cout << to_double("124") << endl;
	cout << to_double("52.1") << endl;
	cout << to_double("0.434") << endl;
	return 0;
}

double to_double(string number){
	double num = 0;
	
	auto point = number.find('.');
	if  (point == string::npos) point = number.length();
	cout << number << " " << point << " - len is " << number.length() << endl;
	for (int i = point; i <= point-number.length()+1; i--) {
		if (point <= 0) num += number[point-i-2] * pow(10, i);
		else num += number[point-i] * pow(10, i);
		cout << i << " = " << num << endl;
	}
	return num;
}

double compute(double first, double second, char operation){
	switch (operation) {
		case '+':
			return first+second;
		case '-':
			return first-second;
		case '*':
			return first*second;
		case '/':
			return first/second;
		default:
			cout << "Found incorrect operation " << operation \
				<< " while computing " << first << operation << second << endl;
	}   
}


string collapse(string expression){ 
	for (;;) {
		auto current = expression.find('*');
		if (current == string::npos) break;
		
		for (int i = current-1; i > 0; i--) {
			
		}
	}
	for (;;) {
		auto current = expression.find('/');
		if (current == string::npos) break;
	}
	for (;;) {
		auto current = expression.find('+');
		if (current == string::npos) break;
	}
	for (;;) {
		auto current = expression.find('-');
		if (current == string::npos) break;
	}
}

string ordering(string expression){
	// Избавление от всех пробелов
	expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());
	// Заключение всего выражения во внешние скобки
	expression.insert(expression.begin(), '(');
	expression.insert(expression.end(), ')');
	for(;;) {
		cout << expression << endl;
		auto closing_bracket = expression.find(')');
		if (closing_bracket == string::npos) break; // Выход из цикла если больше нет ')'
		// Нахождение ближайшей (к закрывающей) открывающей скобки
		auto opening_bracket = expression.find_last_of('(', closing_bracket);
		// Выделение промежуточного выражения 
		string intermediate = expression.substr(opening_bracket+1, closing_bracket-opening_bracket-1);
		cout << intermediate << endl;
		// Замена выделенного выражения на ответ этого выражения
		expression.replace(opening_bracket, closing_bracket-opening_bracket+1, \
		                   collapse(intermediate));
	}
	
	return expression;
}
