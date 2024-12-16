#ifndef ASS_GAME_ULTIMATE_TIC_TAC_TOE_H
#define ASS_GAME_ULTIMATE_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include "BoardGame_Classes.h" // Base classes
using namespace std;


class SmallBoard
{
public:
    vector<vector<char>> board;
    char winner;

    SmallBoard();
    bool update(int x, int y, char symbol);

    bool is_win();
    bool is_full();
};


template <typename T>
class UltimateBoard : public Board<T>
{
public:
    vector<SmallBoard> boards;
    vector<vector<char>> mainBoard;

    UltimateBoard();
    bool update_board( int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int determine_board();
};

enum PlayerType {
    RANDOM_PLAYER,
    REGULAR_PLAYER
};

template <typename T>
class UltimatePlayer : public Player<T>
{
public:
    PlayerType type;
    UltimatePlayer(string name, char symbol);
    void getmove( int &x, int &y) override;
};
template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T>
{
public:
    PlayerType type;
    Ultimate_Random_Player(T symbol);
    void getmove( int &x, int &y) override;
};



SmallBoard::SmallBoard() : board(3, vector<char>(3, ' ')), winner(' ') {}

bool SmallBoard::update(int x, int y, char symbol)
{
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ')
    {
        board[x][y] = symbol;
        return true;
    }
    return false;
}



bool SmallBoard::is_win()
{

    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

bool SmallBoard::is_full()
{
    for (auto &row : board)
        for (char cell : row)
            if (cell == ' ')
                return false;
    return true;
}


template <typename T>
UltimateBoard<T>::UltimateBoard() : mainBoard(3, vector<char>(3, ' ')), boards(9) {}

template <typename T>
bool UltimateBoard<T>::update_board( int x, int y, T symbol)
{
    int smallBoard = determine_board();
    if (smallBoard < 0 || smallBoard >= 9 || boards[smallBoard].winner != ' ')
        return false;

    if (boards[smallBoard].update(x, y, symbol))
    {
        if (boards[smallBoard].is_win())
        {
            boards[smallBoard].winner = symbol;
            mainBoard[smallBoard / 3][smallBoard % 3] = symbol;
        }
        return true;
    }
    return false;
}
template <typename T>
void UltimateBoard<T>::display_board()
{
    cout << "\nUltimate Tic Tac Toe Board:\n";
    for (int i = 0; i < 3; i++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int j = 0; j < 3; j++)
            {
                SmallBoard &sb = boards[i * 3 + j];
                for (int col = 0; col < 3; col++)
                {
                    cout << (sb.board[row][col] == ' ' ? '.' : sb.board[row][col]) << " ";
                }
                cout << " | ";
            }
            cout << "\n";
        }
        cout << string(30, '-') << "\n";
    }
}
template <typename T>
bool UltimateBoard<T>::is_win()
{

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
bool UltimateBoard<T>::is_draw()
{
    for (auto &sb : boards)
        if (sb.winner == ' ' && !sb.is_full())
            return false;
    return true;
}
template <typename T>
bool UltimateBoard<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
int UltimateBoard<T>::determine_board()
{
    int smallBoard;

        cout << "Choose the small board (0-8): ";
        cin >> smallBoard;


    return smallBoard;
}


template <typename T>
UltimatePlayer<T>::UltimatePlayer(string name, char symbol) : Player<T>(name, symbol), type(REGULAR_PLAYER) {}

template <typename T>
void UltimatePlayer<T>::getmove( int &x, int &y)
{
    cout << this->getname() << " (" << this->getsymbol() << "), enter board number (0-8), row, and column: ";
    cin >>  x >> y;

}

template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol):RandomPlayer<T>(symbol),type(RANDOM_PLAYER){};

template <typename T>
void Ultimate_Random_Player<T>::getmove( int &x, int &y)

{

    x = rand() % 3;
    y = rand() % 3;
    cout << "Random move generated: Board " <<", Row " << x << ", Column " << y << endl;


}

#endif // ASS_GAME_ULTIMATE_TIC_TAC_TOE_H
