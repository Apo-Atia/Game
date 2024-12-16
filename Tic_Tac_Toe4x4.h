#ifndef ASS_GAME_TIC_TAC_TOE4X4_H
#define ASS_GAME_TIC_TAC_TOE4X4_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "BoardGame_Classes.h"

using namespace std;



template <typename T>
class Tic_Tac_Toe4x4_Board : public Board<T> {
public:
    Tic_Tac_Toe4x4_Board();
    ~Tic_Tac_Toe4x4_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_move(int x, int y);

};

template <typename T>
Tic_Tac_Toe4x4_Board<T>::Tic_Tac_Toe4x4_Board() {
    this->rows = 4;
    this->columns = 4;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {

            if ((i == 0 && j == 1) || (i == 0 && j == 3) || (i == 3 && j == 0) || (i == 3 && j == 2)) {
                this->board[i][j] = 'X';
            }
            else if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3)) {
                this->board[i][j] = 'o';
            }
            else {

                this->board[i][j] = ' ';
            }
        }
    }
}

template <typename T>
Tic_Tac_Toe4x4_Board<T>::~Tic_Tac_Toe4x4_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}






template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::update_board(int x, int y, T symbol) {
    int i = (x - 1) / 4;
    int j = (x - 1) % 4;


    bool is_human = (symbol != 'o');

    if (is_valid_move(i, j) && this->board[i][j] == symbol) {
        switch (y) {
            case 1:
                if (i > 0 && this->board[i - 1][j] == ' ') {
                    this->board[i - 1][j] = symbol;
                    this->board[i][j] = ' ';
                }
                else if (is_human) {
                    cout << "Invalid move. Try again.\n";
                    return false;
                }
                break;

            case 2:
                if (i < 4 && this->board[i + 1][j] == ' ') {
                    this->board[i + 1][j] = symbol;
                    this->board[i][j] = ' ';
                }
                else if (is_human) {
                    cout << "Invalid move. Try again.\n";
                    return false;
                }
                break;

            case 3:
                if (j < 4 && this->board[i][j + 1] == ' ') {
                    this->board[i][j + 1] = symbol;
                    this->board[i][j] = ' ';
                }
                else if (is_human) {
                    cout << "Invalid move. Try again.\n";
                    return false;
                }
                break;

            case 4:
                if (j > 0 && this->board[i][j - 1] == ' ') {
                    this->board[i][j - 1] = symbol;
                    this->board[i][j] = ' ';
                }
                else if (is_human) {
                    cout << "Invalid move. Try again.\n";
                    return false;
                }
                break;

            default:
                if (is_human) {
                    cout << "Invalid choice. Try again.\n";
                }
                return false;
        }

        return true;
    }

    if (is_human) {
        cout << "Invalid move: Position is not valid.\n";
    }
    return false;
}












template <typename T>
void Tic_Tac_Toe4x4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            cout << " " << this->board[i][j] << " ";
            if (j < this->columns - 1) cout << "|";
        }
        cout << endl;
        if (i < this->rows - 1) {
            for (int j = 0; j < this->columns; j++) {
                cout << "---";
                if (j < this->columns - 1) cout << "+";
            }

            cout << endl;
        }
    }
    cout << "********************\n";
}

template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true;
            }
        }
    }


    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                return true; // ÓáÓáÉ ÊØÇÈÞ
            }
        }
    }

    // ÊÍÞÞ ãä ÇáÃÞØÇÑ (ÇáÞØÑ ÇáÑÆíÓí)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true; // ÓáÓáÉ ÊØÇÈÞ
            }
        }
    }

    // ÊÍÞÞ ãä ÇáÃÞØÇÑ (ÇáÞØÑ ÇáÚßÓí)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                return true; // ÓáÓáÉ ÊØÇÈÞ
            }
        }
    }

    return false;

}

template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::is_draw() {
    return false ;
}

template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::game_is_over() {
    return(is_win() || this->n_moves == 24);
}

template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::is_valid_move(int x, int y) {


    return x >= 0 && x  < this->rows && y >= 0 && y  < this->columns  ;






}

template <typename T>
class Tic_Tac_Toe4x4_Player : public Player<T> {
public:
    Tic_Tac_Toe4x4_Player(string n, T symbol);
    void getmove(int& x, int& y) override;

};

template <typename T>
Tic_Tac_Toe4x4_Player<T>::Tic_Tac_Toe4x4_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void Tic_Tac_Toe4x4_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << " (" << this->getsymbol() << ") - Entetr the numper of Cell AND Enter 1: UP  OR 2: Dwon  OR 3: RIGHT OR 4: LEFT): ";
    cin >> x >> y;
}


// TicTacToe5x5_RandomPlayer class template
template <typename T>
class Tic_Tac_Toe4x4_RandomPlayer : public RandomPlayer<T> {
public:
    Tic_Tac_Toe4x4_RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};



// Implementations for TicTacToe5x5_RandomPlayer class
template <typename T>
Tic_Tac_Toe4x4_RandomPlayer<T>::Tic_Tac_Toe4x4_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    /* srand(time(0));*/   ////
}

template <typename T>
void Tic_Tac_Toe4x4_RandomPlayer<T>::getmove(int& x, int& y) {
    srand(static_cast<unsigned>(time(0)));
    int rndcell = rand() % (9 + 1);
    x = --rndcell / sqrt(9);
    y = rand() % 4 + 1;
}





#endif //ASS_GAME_TIC_TAC_TOE4X4_H
