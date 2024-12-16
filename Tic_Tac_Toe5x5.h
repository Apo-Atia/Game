#ifndef ASS_GAME_TIC_TAC_TOE5X5_H
#define ASS_GAME_TIC_TAC_TOE5X5_H


#include <iostream>
#include <vector>
#include "BoardGame_Classes.h"
using namespace std;


template <typename T>
class Tic_Tac_Toe5x5_Board : public Board<T> {
public:
    Tic_Tac_Toe5x5_Board();
    ~Tic_Tac_Toe5x5_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_move(int x, int y);
};


template <typename T>
class TicTacToe5x5_Player : public Player<T> {
public:
    TicTacToe5x5_Player(string n, T symbol);
    void getmove(int& x, int& y) override;
};


template <typename T>
class TicTacToe5x5_RandomPlayer : public RandomPlayer<T> {
public:
    TicTacToe5x5_RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};



template <typename T>
Tic_Tac_Toe5x5_Board<T>::Tic_Tac_Toe5x5_Board() {
    this->rows = 5;
    this->columns = 5;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
}

template <typename T>
Tic_Tac_Toe5x5_Board<T>::~Tic_Tac_Toe5x5_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool Tic_Tac_Toe5x5_Board<T>::update_board(int x, int y, T symbol) {
    if (is_valid_move(x, y)) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Tic_Tac_Toe5x5_Board<T>::display_board() {
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
        }
        cout << endl;
    }
}

template <typename T>
bool Tic_Tac_Toe5x5_Board<T>::is_win() {
    return false;
}

template <typename T>
bool Tic_Tac_Toe5x5_Board<T>::is_draw() {
    return false;
}

template<typename T>
bool Tic_Tac_Toe5x5_Board<T>::is_valid_move(int x, int y) {
    return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ';
}

template <typename T>
bool Tic_Tac_Toe5x5_Board<T>::game_is_over() {
    if (this->n_moves == 24) {

        int x_count = 0, o_count = 0;


        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j <= this->columns - 3; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2]) {
                    if (this->board[i][j] == 'X') x_count++;
                    if (this->board[i][j] == 'o') o_count++;
                }
            }
        }


        for (int i = 0; i <= this->rows - 3; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j]) {
                    if (this->board[i][j] == 'X') x_count++;
                    if (this->board[i][j] == 'o') o_count++;
                }
            }
        }


        for (int i = 0; i <= this->rows - 3; i++) {
            for (int j = 0; j <= this->columns - 3; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2]) {
                    if (this->board[i][j] == 'X') x_count++;
                    if (this->board[i][j] == 'o') o_count++;
                }
            }
        }


        for (int i = 0; i <= this->rows - 3; i++) {
            for (int j = 2; j < this->columns; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i][j] == this->board[i + 2][j - 2]) {
                    if (this->board[i][j] == 'X') x_count++;
                    if (this->board[i][j] == 'o') o_count++;
                }
            }
        }


        cout << "Game Over!\n";
        cout << "Player X groups: " << x_count << "\n";
        cout << "Player O groups: " << o_count << "\n";

        if (x_count > o_count) {
            cout << "Player X wins!\n";
        }
        else if (x_count < o_count) {
            cout << "Player O wins!\n";
        }
        else {
            cout << "It's a drwa!\n";
        }

        return true;
    }

    return false;
}

template <typename T>
TicTacToe5x5_Player<T>::TicTacToe5x5_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void TicTacToe5x5_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << " (" << this->getsymbol() << ") - Enter move (row, col): ";
    cin >> x >> y;

    Tic_Tac_Toe5x5_Board<T>* specificBoard = dynamic_cast<Tic_Tac_Toe5x5_Board<T>*>(this->boardPtr);
    while (specificBoard && !specificBoard->is_valid_move(x, y)) {
        cout << "Invalid move! Please try again.\n";
        cin >> x >> y;
    }
}

template <typename T>
TicTacToe5x5_RandomPlayer<T>::TicTacToe5x5_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(time(0));
}

template <typename T>
void TicTacToe5x5_RandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 5;
    y = rand() % 5;
}



#endif //ASS_GAME_TIC_TAC_TOE5X5_H
