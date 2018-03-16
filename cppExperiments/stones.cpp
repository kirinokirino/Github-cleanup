#include <iostream>
using namespace std;

static int winCondition = 20;
void gameLoop();
void nextGame();
int makeTurn();
void showInfo();
int playersTurn(int turn);

int main(){
        gameLoop();
        return 0;
}

void nextGame(){
        char answer = 'q';
        while (true) {
                cout << "Хотите ли вы сыграть ещё раз? (y/n): ";
                cin >> answer;
                if (answer == 'y' || answer == 'n') break;
                else cout << "Команда некорректна, попытайтесь ещё раз." << endl;
        }
        if (answer == 'n') {
                cout << "Выход из игры" << endl;
        } else gameLoop();
}

void showInfo(int turn, int stones){
        cout << "Наступил " << turn << " ход." << endl;
        cout << "В данный момент в куче " << stones << " камней." << endl;
        cout << "Для окончания игры нужно " << winCondition-stones << " камней." << endl;
        cout << "Игрок #" << playersTurn(turn) << ", введите добавляемое количество камней (1,2,3)" << endl;
}

int makeTurn(){
        char answer = 'q';
        while (true) {
                cin >> answer;
                if (answer == '1' || answer == '2' || answer == '3') break;
                else cout << "Команда некорректна, попытайтесь ещё раз." << endl;
        }
        switch (answer) {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        }
        return -1;
}

void gameLoop(){
        int turn = 0;
        int stones = 0;
        while (stones < winCondition) {
                showInfo(turn, stones);
                stones += makeTurn();
                turn++;
        }
        cout << "Игра окончена. победил игрок #" << playersTurn(turn) << '.' << endl;
        nextGame();
}

int playersTurn(int turn){
        if (turn%2 == 0) return 2;
        else return 1;
}
