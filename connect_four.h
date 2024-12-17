#include "BoardGame_Classes.h"
#include<bits/stdc++.h>
template<typename T>
class connect_four:public Board<T>{
public:
  connect_four();
  bool update_board(int x, int y, T symbol);
  void display_board();
  bool is_win();
  bool is_draw();
  bool game_is_over();
};
template <typename T>
class connect_four_player : public Player<T>
{
public:
  connect_four_player(string name, T symbol);
  void getmove(int &x, int &y);
};
template <typename T>
class connect_four_Random_player : public RandomPlayer<T>
{
public:
  connect_four_Random_player(T symbol);
  void getmove(int &x, int &y);
};

//=======================================IMLEMENTAION

  template <typename T>
  connect_four<T>::connect_four()
  {
    this->rows = 6;
    this->columns = 7;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
      this->board[i] = new char[this->columns];
      for (int j = 0; j < this->columns; j++)
      {
        this->board[i][j] = 0;
      }
    }
    this->n_moves = 0;
  }
  template <typename T>
  bool connect_four<T>::update_board(int x, int y, T mark)
  {
    if (y < 0 || y >= this->columns)
      return false; 

    for (int i = this->rows - 1; i >= 0; i--)
    { 
      if (this->board[i][y] == 0)
      {
        this->board[i][y] = toupper(mark);
        this->n_moves++;
        return true;
      }
    }
    return false; 
  }

  template <typename T>
  void connect_four<T>::display_board()
  {
    for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
      {
        cout << "| " << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " ";
      }
      cout << "|\n";
    }
    cout << string(this->columns * 4, '-') << "\n";
  }

  template <typename T>
  bool connect_four<T>::is_win()
  {
    for (int i = 0; i < 6; i++)
    { 
      for (int j = 0; j <= 7 - 4; j++)
      { 
        if (this->board[i][j] != 0 &&
            this->board[i][j] == this->board[i][j + 1] &&
            this->board[i][j] == this->board[i][j + 2] &&
            this->board[i][j] == this->board[i][j + 3])
        {
          return true;
        }
      }
    }

    for (int i = 0; i <= 6 - 4; i++)
    { 
      for (int j = 0; j < 7; j++)
      {
        if (this->board[i][j] != 0 &&
            this->board[i][j] == this->board[i + 1][j] &&
            this->board[i][j] == this->board[i + 2][j] &&
            this->board[i][j] == this->board[i + 3][j])
        {
          return true;
        }
      }
    }

    for (int i = 0; i <= 6 - 4; i++)
    { 
      for (int j = 0; j <= 7 - 4; j++)
      { 
        if (this->board[i][j] != 0 &&
            this->board[i][j] == this->board[i + 1][j + 1] &&
            this->board[i][j] == this->board[i + 2][j + 2] &&
            this->board[i][j] == this->board[i + 3][j + 3])
        {
          return true;
        }
      }
    }

    for (int i = 0; i <= 6 - 4; i++)
    { 
      for (int j = 3; j < 7; j++)
      { 
        if (this->board[i][j] != 0 &&
            this->board[i][j] == this->board[i + 1][j - 1] &&
            this->board[i][j] == this->board[i + 2][j - 2] &&
            this->board[i][j] == this->board[i + 3][j - 3])
        {
          return true;
        }
      }
    }

    return false;
  }

  template <typename T>
  bool connect_four<T>::is_draw()
  {
    for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
      {
        if (this->board[i][j] == 0)
          return false;
      }
    }
    return !is_win(); 
  }

  template <typename T>
  bool connect_four<T>::game_is_over()
  {
    return is_win() || is_draw();
  }

  template <typename T>
  connect_four_player<T>::connect_four_player(string name, T symbol) : Player<T>(name, symbol) {}

  template <typename T>
  void connect_four_player<T>::getmove(int &x, int &y)
  {
    cout << "\nPlease enter your move x from 0 to 6 and y (0 to 7) separated by spaces: ";
    cin >> x >> y;
  }
  template <typename T>
  connect_four_Random_player<T>::connect_four_Random_player(T symbol) : RandomPlayer<T>(symbol)
  {
    
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
  }

  template <typename T>
  void connect_four_Random_player<T>::getmove(int &x, int &y)
  {
    x = rand() % 6; // Random number between 0 and 2
    y = rand() % 7;
  }
