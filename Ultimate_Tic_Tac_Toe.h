#ifndef ASS_GAME_ULTIMATE_TIC_TAC_TOE_H
#define ASS_GAME_ULTIMATE_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include "BoardGame_Classes.h" 
using namespace std;


class SmallBoard {
public:
    vector<vector<char>> board;
    char winner;

    SmallBoard();
    bool update(int row, int col, char symbol);
    bool is_win();
    bool is_full();
};

template <typename T>
class UltimateBoard : public Board<T> {
public:
    vector<SmallBoard> boards;
    vector<vector<char>> mainBoard;

    UltimateBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw() override;
    bool game_is_over();
};

SmallBoard::SmallBoard() : board(3, vector<char>(3, ' ')), winner(' ') {}

bool SmallBoard::update(int row, int col, char symbol) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = symbol;
        return true;
    }
    return false;
}

bool SmallBoard::is_win() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

bool SmallBoard::is_full() {
    for (auto& row : board) {
        for (char cell: row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
UltimateBoard<T>::UltimateBoard() : mainBoard(3, vector<char>(3, ' ')), boards(9) {}

template <typename T>
bool UltimateBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= 9 || boards[x].winner != ' ')
        return false;

    int row = (y - 1) / 3;
    int col = (y - 1) % 3;

    if (boards[x].update(row, col, symbol)) {
        if (boards[x].is_win()) {
            boards[x].winner = symbol;
            mainBoard[x / 3][x % 3] = symbol;
        }
        return true;
    }
    return false;
}

template <typename T>
void UltimateBoard<T>::display_board() {
    cout << "\nUltimate Tic Tac Toe Board:\n";

  
    for (int i = 0; i < 9; i++) {
        cout << i + 1 << " winner : ";
        if (boards[i].winner != ' ')
            cout << boards[i].winner;
        else
            cout << "-";
        cout << "   ";
        if ((i + 1) % 3 == 0) cout << "\n";
    }

    cout << string(50, '-') << "\n";


    for (int row = 0; row < 3; row++) { 
        for (int line = 0; line < 3; line++) { 
            for (int col = 0; col < 3; col++) { 
                SmallBoard &sb = boards[row * 3 + col];
                for (int c = 0; c < 3; c++) { 
                    cout << (sb.board[line][c] == ' ' ? '.' : sb.board[line][c]) << " ";
                }
                cout << "| ";
            }
            cout << "\n";
        }
        cout << string(50, '-') << "\n";
    }
}


template <typename T>
bool UltimateBoard<T>::is_win() {
    for (int i = 0; i < 3; i++)
    {
        if (mainBoard[i][0] != ' ' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2])
            return true;
        if (mainBoard[0][i] != ' ' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i])
            return true;
    }
    if (mainBoard[0][0] != ' ' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2])
        return true;
    if (mainBoard[0][2] != ' ' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0])
        return true;

    return false;
}

template <typename T>
bool UltimateBoard<T>::is_draw() {

    for (auto& sb : boards) {
        if (!sb.is_full() && sb.winner == ' ') {
            return false;
        }
    }
    return !is_win();
}


template <typename T>
bool UltimateBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
class UltimatePlayer : public Player<T> {
public:
    UltimatePlayer(string name, char symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
UltimatePlayer<T>::UltimatePlayer(string name, char symbol) : Player<T>(name, symbol) {}

template <typename T>
void UltimatePlayer<T>::getmove(int& x, int& y) {
    cout << "Enter small board number (1-9): ";
    cin >> x;

    x -= 1;

    while (x < 0 || x >= 9) {
        cout << "Invalid board number! Enter a number between 1 and 9: ";
        cin >> x;
        x -= 1;
    }
    cout << "Enter cell number (1-9) in board " << x + 1 << ": ";
    cin >> y;
}


template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 9;
    y = rand() % 9 + 1;
}

#endif // ASS_GAME_ULTIMATE_TIC_TAC_TOE_H
