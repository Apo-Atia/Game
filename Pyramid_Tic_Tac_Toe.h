#ifndef ASS_GAME_PYRAMID_TIC_TAC_TOE_H
#define ASS_GAME_PYRAMID_TIC_TAC_TOE_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    vector<vector<T>> board;
};

template <typename T>
class PyramidPlayer : public Player<T> {
public:
    PyramidPlayer(std::string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};



template <typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;
    this->columns = 5;
    this->board = {
            {' '},
            {' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '}
    };

    this->n_moves = 0;
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void PyramidBoard<T>::display_board() {
    cout << "\nCurrent Board State:\n";

    cout << string(20, ' ');
    cout << "|" << "(" << 0 << "," << 0 << ")";
    if (this->board[0][0] != ' ') {
        cout << " " << this->board[0][0];
    }
    cout << "|\n\n";

    cout << string(10, ' ');
    for (int j = 0; j < 3; j++) {
        cout << "|(" << 1 << "," << j << ")";
        if (this->board[1][j] != ' ') {
            cout << " " << this->board[1][j];
        }
        cout << "|   ";
    }
    cout << "\n\n";

    for (int j = 0; j < 5; j++) {
        cout << "|(" << 2 << "," << j << ")";
        if (this->board[2][j] != ' ') {
            cout << " " << this->board[2][j];
        }
        cout << "|   ";
    }
    cout << "\n";
}

template <typename T>
bool PyramidBoard<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j + 2 < this->board[i].size(); j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2]) {
                return true;
            }
        }
    }


    for (int j = 0; j < this->columns; j++) {
        if (j < this->board[0].size() &&
            this->board[0][j] != ' ' &&
            this->board[0][j] == this->board[1][j] &&
            this->board[1][j] == this->board[2][j]) {
            return true;
        }
    }


    if (this->board[0][0] != ' ' &&
        this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2]) {
        return true;
    }

    if (this->board[0][0] != ' ' &&
        this->board[0][0] == this->board[1][2] &&
        this->board[1][2] == this->board[2][4]) {
        return true;
    }


    return false;
}


template <typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}


template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
PyramidPlayer<T>::PyramidPlayer(std::string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    std::cout << "\n" << this->getname() << ", enter your move (row and column separated by space like this 1 0): ";
    std::cin >> x >> y;
}


template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Pyramid Player";
    srand(static_cast<unsigned int>(time(0)));
}


template <typename T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y) {
    while (true) {
        x = rand() % this->dimension;


        if (x == 0) {
            y = 0;
        } else if (x == 1) {
            y = rand() % 3;
        } else if (x == 2) {
            y = rand() % 5;
        }

        return;
    }
}

#endif //ASS_GAME_PYRAMID_TIC_TAC_TOE_H
