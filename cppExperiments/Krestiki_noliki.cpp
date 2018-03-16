#include <iostream>
#include <utility>
using namespace std;

const int field_size = 3;
void field_draw(char field[field_size][field_size]);
pair<int, int> make_turn();
char turn_end(char field[field_size][field_size]);

int main () {
  char field[field_size][field_size];
  for (int i = 0; i < field_size; i++) {
    for (int j = 0; j < field_size; j++) {
      field[i][j] = ' ';
    }
  }
  
  char player = 'X';
  for (int i = 0; i < field_size*field_size; i++) {
    field_draw(field);
    
    bool check = true;
    do {
      pair<int, int> t = make_turn();
      if (field[t.first][t.second] == ' ') {
        field[t.first][t.second] = player;
        check = false;
      } else {
        cout << "Введённое поле занято! Попробуйте ещё раз" << endl;
      }
    } while (check);
    
    if (turn_end(field) == 'W') {
      cout << "Победил игрок " << player << endl;
      break;
    }
    
    if (player == 'X') player = 'O';
    else player = 'X';
  }
  cout << "Игра окончена.  " << endl;
  return 0;
}

pair<int, int> make_turn(){
  int a = -1, b = -1;
  while (true) {
    cout << "Введите номер строки: ";
    cin >> a;
    if (a >= 0 && a < field_size) break;
    else cout << "Введите номер строки в границах поля!" << endl;
  }
  while (true) {
    cout << "Введите номер столбца: ";
    cin >> b;
    if (b >= 0 && b < field_size) break;
    else cout << "Введите номер столбца в границах поля!" << endl;
  }
  return make_pair(a, b);
}

char turn_end(char field[field_size][field_size]) {
  
  if (       (field[0][0] == 'X' && field[1][0] == 'X' && field[2][0] == 'X') ||
             (field[0][1] == 'X' && field[1][1] == 'X' && field[2][1] == 'X') ||
             (field[0][2] == 'X' && field[1][2] == 'X' && field[2][2] == 'X') ||

             (field[0][0] == 'X' && field[0][1] == 'X' && field[0][2] == 'X') ||
             (field[1][0] == 'X' && field[1][1] == 'X' && field[1][2] == 'X') ||
             (field[2][0] == 'X' && field[2][1] == 'X' && field[2][2] == 'X') ||

             (field[0][0] == 'X' && field[1][1] == 'X' && field[2][2] == 'X') ||
             (field[2][0] == 'X' && field[1][1] == 'X' && field[0][2] == 'X') ) {
    return 'W';
  } else if ((field[0][0] == 'O' && field[1][0] == 'O' && field[2][0] == 'O') ||
             (field[0][1] == 'O' && field[1][1] == 'O' && field[2][1] == 'O') ||
             (field[0][2] == 'O' && field[1][2] == 'O' && field[2][2] == 'O') ||

             (field[0][0] == 'O' && field[0][1] == 'O' && field[0][2] == 'O') ||
             (field[1][0] == 'O' && field[1][1] == 'O' && field[1][2] == 'O') ||
             (field[2][0] == 'O' && field[2][1] == 'O' && field[2][2] == 'O') ||

             (field[0][0] == 'O' && field[1][1] == 'O' && field[2][2] == 'O') ||
             (field[2][0] == 'O' && field[1][1] == 'O' && field[0][2] == 'O')) {
    return 'W';
  } else return 'N';
}

void field_draw(char field[field_size][field_size]) {
  cout << "-------" << endl;
  for (int i = 0; i < field_size; i++) {
    cout << '|';
    for (int j = 0; j < field_size; j++) {
      cout << field[i][j] << '|';
    }
    cout << endl;
    cout << "-------" << endl;
  }
}
