#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>

















using namespace std;

// Board class template
template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;
};

// Player class template
template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;
                                                                                     
public:
    Player(string n, T symbol);
    Player(T symbol);
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
    virtual void getmove(int& x, int& y) = 0;
};





// RandomPlayer 

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



// GameManager class template

template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    GameManager(Board<T>*, Player<T>* playerPtr[2]);

    void run();
};


template <typename T>
Player<T>::Player(std::string n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

// Constructor for Player with only a symbol (e.g., for computer players)
template <typename T>
Player<T>::Player(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

template <typename T>
T Player<T>::getsymbol() {
    return this->symbol;
}

template <typename T>
string Player<T>::getname() {
    return this->name;
}

template <typename T>
void Player<T>::setBoard(Board<T>* b) {
    this->boardPtr = b;
}

// Implementations for RandomPlayer class
template <typename T>
RandomPlayer<T>::RandomPlayer(T symbol) : Player<T>(symbol) {}

//template <typename T>
//void RandomPlayer<T>::getmove(int& x, int& y) {
//    x = rand() % 5;
//    y = rand() % 5;
//}








// TicTacToe5x5_Board class template
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
GameManager<T>::GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];

 
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
TicTacToe5x5_Board<T>::TicTacToe5x5_Board() {
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
TicTacToe5x5_Board<T>::~TicTacToe5x5_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool TicTacToe5x5_Board<T>::update_board(int x, int y, T symbol) {
    if (is_valid_move(x, y)) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
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
        }
        cout << endl;
    }
}

template <typename T>
bool TicTacToe5x5_Board<T>::is_win() {
    return false;
}

template <typename T>
bool TicTacToe5x5_Board<T>::is_draw() {
    return false;
}

template<typename T>
bool TicTacToe5x5_Board<T>::is_valid_move(int x, int y) {
    return x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ';
}

template <typename T>
bool TicTacToe5x5_Board<T>::game_is_over() {
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

    TicTacToe5x5_Board<T>* specificBoard = dynamic_cast<TicTacToe5x5_Board<T>*>(this->boardPtr);
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



int main() {
    int choice;
    Player<char>* players[2];
    TicTacToe5x5_Board<char>* board = new TicTacToe5x5_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to FCAI TicTacToe 5x5 Game. :)\n";

    
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[0] = new TicTacToe5x5_Player<char>(player1Name, 'X');
        break;
    case 2:
        players[0] = new TicTacToe5x5_RandomPlayer<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

   
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new TicTacToe5x5_Player<char>(player2Name, 'o');
        break;
    case 2:
        players[1] = new TicTacToe5x5_RandomPlayer<char>('o');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }


    GameManager<char> game(board, players);
    game.run();

    
    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}

    



