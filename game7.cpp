#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    /// Return true if move is valid and put it on the board
    /// within board boundaries in an empty cell
    /// Return false otherwise
    virtual bool update_board(int x, int y, T symbol) = 0;

    /// Display the board and the pieces on it
    virtual void display_board() = 0;

    /// Returns true if there is any winner
    virtual bool is_win() = 0;

    /// Return true if all moves are done and no winner
    virtual bool is_draw() = 0;

    /// Return true if the game is over
    virtual bool game_is_over() = 0;
};

template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;  // Pointer to the board
public:
    /// Two constructors to initiate players
    /// Give the player a symbol to use in playing
    /// It can be X, O, or others
    /// Optionally, you can give them a name
    Player(string n, T symbol);
    Player(T symbol); // For computer players

    virtual void getmove(int& x, int& y) = 0;
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
};

/// This class represents a random computer player
/// that generates random positions x, y
/// If invalid, the game manager asks to regenerate
template <typename T>
class RandomPlayer : public Player<T> {
protected:
    int dimension;
public:
    // Take a symbol and pass it to the parent
    RandomPlayer(T symbol);
    // Generate a random move
    virtual void getmove(int& x, int& y) = 0;
};

template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    GameManager(Board<T>*, Player<T>* playerPtr[2]);

    void run();
};


//--------------------------------------- IMPLEMENTATION



template <typename T>
GameManager<T>::GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];

   /* players[0]->setBoard(boardPtr);
    players[1]->setBoard(boardPtr);*/
}

template <typename T>
void GameManager<T>::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            players[i]->getmove(x, y);
            while (!boardPtr->update_board(x, y, players[i]->getsymbol())) {
                players[i]->getmove(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}

template <typename T>
Player<T>::Player(std::string n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

template <typename T>
Player<T>::Player(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

template <typename T>
RandomPlayer<T>::RandomPlayer(T symbol) : Player<T>(symbol) {}

template <typename T>
std::string Player<T>::getname() {
    return this->name;
}

template <typename T>
T Player<T>::getsymbol() {
    return this->symbol;
}

template <typename T>
void Player<T>::setBoard(Board<T>* b) {
    this->boardPtr = b;
}

// ---------------------------------- Specific TicTacToe5x5 Classes

template <typename T>
class TicTacToe5x5_Board : public Board<T> {
public:
    TicTacToe5x5_Board();
    ~TicTacToe5x5_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_move(int x, int y);

};

template <typename T>
TicTacToe5x5_Board<T>::TicTacToe5x5_Board() {
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
TicTacToe5x5_Board<T>::~TicTacToe5x5_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

//template <typename T>
//TicTacToe5x5_Board<T>::~TicTacToe5x5_Board() {
//    for (int i = 0; i < this->rows; i++) {
//        delete[] this->board[i];
//    }
//    delete[] this->board;
//}
//
//template <typename T>
//bool TicTacToe5x5_Board<T>::update_board(int x, int y, T symbol) {
//
//    int i = (x - 1) / 4;
//    int j = (x - 1) % 4;
//    if (is_valid_move(i, j) && this->board[i][j] == symbol) {
//
//
//
//
//
//
//
//        switch (y) {
//        case 1: // UP
//            if (i > 0 && this->board[i - 1][j] == ' ') { // ������ �� ������ ������� ������   
//                this->board[i - 1][j] = symbol;
//                this->board[i][j] = ' ';
//            }
//            else {
//                cout << "Invalid move. Try again.\n";
//                this->board[i][j] = symbol; // ����� ����� ��� ���� ������ ��� �����  
//                return false;
//            }
//            break;
//
//        case 2: // DOWN
//            if (i < 4 && this->board[i + 1][j] == ' ') {
//                this->board[i + 1][j] = symbol;
//                this->board[i][j] = ' ';
//            }
//            else {
//                cout << "Invalid move. Try again.\n";
//                this->board[i][j] = symbol;
//                return false;
//            }
//            break;
//
//        case 3: // RIGHT
//            if (j < 4 && this->board[i][j + 1] == ' ') {
//                this->board[i][j + 1] = symbol;
//                this->board[i][j] = ' ';
//            }
//            else {
//                cout << "Invalid move. Try again.\n";
//                this->board[i][j] = symbol;
//                return false;
//            }
//            break;
//
//        case 4: // LEFT
//            if (j > 0 && this->board[i][j - 1] == ' ') {
//                this->board[i][j - 1] = symbol;
//                this->board[i][j] = ' ';
//            }
//            else {
//                cout << "Invalid move. Try again.\n";
//                this->board[i][j] = symbol;
//                return false;
//            }
//            break;
//
//        default:
//            cout << "Invalid choice. Try again.\n";
//            this->board[i][j] = symbol;
//            return false;
//        }
//
//        return true; // ��� �� ������ �����
//    }
//
//    cout << "Invalid move: Position is not valid.\n";
//    return false; // ��� ���� ������ ��� �����
//}







template <typename T>
bool TicTacToe5x5_Board<T>::update_board(int x, int y, T symbol) {
    int i = (x - 1) / 4;
    int j = (x - 1) % 4;

    // Assume computer's symbol or name is predefined as 'C' or "Computer"
    bool is_human = (symbol != 'o'); // Adjust this condition based on your implementation.  

    if (is_valid_move(i, j) && this->board[i][j] == symbol) {
        switch (y) {
        case 1: // UP
            if (i > 0 && this->board[i - 1][j] == ' ') {
                this->board[i - 1][j] = symbol;
                this->board[i][j] = ' ';
            }
            else if (is_human) {
                cout << "Invalid move. Try again.\n";
                return false;
            }
            break;

        case 2: // DOWN
            if (i < 4 && this->board[i + 1][j] == ' ') {
                this->board[i + 1][j] = symbol;
                this->board[i][j] = ' ';
            }
            else if (is_human) {
                cout << "Invalid move. Try again.\n";
                return false;
            }
            break;

        case 3: // RIGHT
            if (j < 4 && this->board[i][j + 1] == ' ') {
                this->board[i][j + 1] = symbol;
                this->board[i][j] = ' ';
            }
            else if (is_human) {
                cout << "Invalid move. Try again.\n";
                return false;
            }
            break;

        case 4: // LEFT
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
void TicTacToe5x5_Board<T>::display_board() {
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
bool TicTacToe5x5_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true; // ����� �����
            }
        }
    }

    // ���� �� �������
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                return true; // ����� �����
            }
        }
    }

    // ���� �� ������� (����� �������)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true; // ����� �����
            }
        }
    }

    // ���� �� ������� (����� ������)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                return true; // ����� �����
            }
        }
    }

    return false;

}

template <typename T>
bool TicTacToe5x5_Board<T>::is_draw() {
    return false ;
}

template <typename T>
bool TicTacToe5x5_Board<T>::game_is_over() {
    return(is_win() || this->n_moves == 24);
}

template <typename T>
bool TicTacToe5x5_Board<T>::is_valid_move(int x, int y) {


    return x >= 0 && x  < this->rows && y >= 0 && y  < this->columns  ;    






}

template <typename T>
class TicTacToe5x5_Player : public Player<T> {
public:
    TicTacToe5x5_Player(string n, T symbol);
    void getmove(int& x, int& y) override;                              // cout << "Entetr the numper of Cell AND Enter 1: UP  OR 2: Dwon  OR 3: RIGHT OR 4: LEFT\n";
                                                                        // cout << "\n"; 
};

template <typename T>
TicTacToe5x5_Player<T>::TicTacToe5x5_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void TicTacToe5x5_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << " (" << this->getsymbol() << ") - Entetr the numper of Cell AND Enter 1: UP  OR 2: Dwon  OR 3: RIGHT OR 4: LEFT): ";
    cin >> x >> y;
}


// TicTacToe5x5_RandomPlayer class template
template <typename T>
class TicTacToe5x5_RandomPlayer : public RandomPlayer<T> {
public:
    TicTacToe5x5_RandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};



// Implementations for TicTacToe5x5_RandomPlayer class
template <typename T>
TicTacToe5x5_RandomPlayer<T>::TicTacToe5x5_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
   /* srand(time(0));*/   ////
}

template <typename T>
void TicTacToe5x5_RandomPlayer<T>::getmove(int& x, int& y) {
    srand(static_cast<unsigned>(time(0)));
    int rndcell = rand() % (9 + 1);
    x = --rndcell / sqrt(9);
    y = rand() % 4 + 1;
}





int main() {

    srand(time(0)); 
    int choice;
    Player<char>* players[2];
    TicTacToe5x5_Board<char>* board = new TicTacToe5x5_Board<char>();

    cout << "Welcome to FCAI Misere Tic Tac Toe Game. :)\n";

    // ����� ������ ����� Player X
    cout << "Enter Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        players[0] = new TicTacToe5x5_Player<char>("Player X ", 'X');
        break;
    case 2:
        players[0] = new TicTacToe5x5_RandomPlayer<char>('X');
        break;
    default:
        cout << "Invalid choice for Player X. Exiting the game.\n";
        delete board;
        return 1;
    }

    // ����� ������ ������ Player O
    cout << "Enter Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new TicTacToe5x5_Player<char>("Player O ", 'o');
        break;
    case 2:
        players[1] = new TicTacToe5x5_RandomPlayer<char>('o');
        break;
    default:
        cout << "Invalid choice for Player O. Exiting the game.\n";
        delete players[0];  // ���� �� ��� ������ �����
        delete board;
        return 1;
    }

    // ����� ���� ������ ������ ������
    GameManager<char> game(board, players);
    game.run();

    // ����� �������
    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}


