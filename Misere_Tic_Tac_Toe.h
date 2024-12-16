#ifndef ASS_GAME_MISERE_TIC_TAC_TOE_H
#define ASS_GAME_MISERE_TIC_TAC_TOE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Misere_Tic_Tac_Toe_Board : public Board<T> {
public:
    Misere_Tic_Tac_Toe_Board();
    ~Misere_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_move(int x, int y);
};

template <typename T>
Misere_Tic_Tac_Toe_Board<T>::Misere_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
}

template <typename T>
Misere_Tic_Tac_Toe_Board<T>::~Misere_Tic_Tac_Toe_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool Misere_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (is_valid_move(x, y)) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Misere_Tic_Tac_Toe_Board<T>::display_board() {
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
bool Misere_Tic_Tac_Toe_Board<T>::is_win() {
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
                return true;
            }
        }
    }


    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true;
            }
        }
    }


    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                return true;
            }
        }
    }

    return false;

}

template <typename T>
bool Misere_Tic_Tac_Toe_Board<T>::is_draw() {
    return (!is_win() && this->n_moves == 25);
}

template <typename T>
bool Misere_Tic_Tac_Toe_Board<T>::game_is_over() {
    return(is_win() || is_draw() || this->n_moves == 24);
}

template <typename T>
bool Misere_Tic_Tac_Toe_Board<T>::is_valid_move(int x, int y) {
    return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ';
}

template <typename T>
class Misere_Tic_Tac_Toe_Player : public Player<T> {
public:
    Misere_Tic_Tac_Toe_Player(string n, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
Misere_Tic_Tac_Toe_Player<T>::Misere_Tic_Tac_Toe_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void Misere_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << " (" << this->getsymbol() << ") - Enter move (row, col): ";
    cin >> x >> y;
}



template <typename T>
class Misere_Tic_Tac_Toe_RandomPlayer : public RandomPlayer<T> {
public:
    Misere_Tic_Tac_Toe_RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};




template <typename T>
Misere_Tic_Tac_Toe_RandomPlayer<T>::Misere_Tic_Tac_Toe_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(time(0));
}

template <typename T>
void Misere_Tic_Tac_Toe_RandomPlayer<T>::getmove(int& x, int& y) {
    srand(static_cast<unsigned>(time(0)));
    int rndcell = rand() % (9 + 1);
    x = --rndcell / sqrt(9);
    y = rndcell % int(sqrt(9));
}




#endif
