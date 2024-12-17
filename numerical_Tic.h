#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
template <typename T>
class Tic_board : public Board<T>
{
public:
  Tic_board();
  bool update_board(int x, int y, T symbol);
  void display_board();
  bool is_win();
  bool is_draw();
  bool game_is_over();
};
template <typename T>
class Tic_player : public Player<T>
{
private:
  vector<int> numbers;

public:
  Tic_player(string n, T sympol, vector<int> nums);
  void getmove(int &x, int &y);
};
template <typename T>
class Tic_random_player : public RandomPlayer<T>
{
  vector<int> numbers;
public:
  Tic_random_player(T,vector<int>nums);
  void getmove(int &x, int &y) override;
};

//============================================IMPLEMENTATION
template <typename T>
Tic_board<T>::Tic_board()
{
  this->rows = this->columns = 3;
  this->board = new int *[this->rows];
  for (int i = 0; i < this->rows; i++)
    this->board[i] = new int[this->columns];

  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->columns; j++)
    {
      this->board[i][j] = 0;
    }
  }
}
template <typename T>
bool Tic_board<T>::update_board(int x, int y, T symbol)
{
  if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0))
  {

    this->n_moves++;
    this->board[x][y] = symbol;

    return true;
  }
  return false;
}

template <typename T>
void Tic_board<T>::display_board()
{
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->columns; j++)
    {
      cout << (this->board[i][j] ? to_string(this->board[i][j]) : " ") << " ";
      if (j < this->columns - 1)
        cout << "| ";
    }
    cout << endl;
    if (i < this->rows - 1)
      cout << "---+---+---" << endl;
  }
}

template <typename T>
bool Tic_board<T>::is_win()
{
  for (int i = 0; i < this->rows; i++)
  {
    if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
        (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0))
    {
      return true;
    }
  }

  if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) ||
      (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 && this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0))
  {
    return true;
  }

  return false;
}

template <typename T>
bool Tic_board<T>::is_draw()
{
  return this->n_moves == 9 && !is_win();
}
template <typename T>

bool Tic_board<T>::game_is_over()
{
  return is_win() || is_draw();
}
template <typename T>
Tic_player<T>::Tic_player(string name, T symbol, vector<int> nums) : Player<T>(name, symbol), numbers(nums) {}


template <typename T>
void Tic_player<T>::getmove(int &x, int &y)
{
  cout << "Enter your position (x and y) from 0 to 2:\n";
  cin >> x >> y;

  vector<int> available_numbers = numbers;

  cout << "Available numbers: { ";
  for (auto &i : available_numbers)
    cout << i << " ";
  cout << "}\n";

  cout << "Pick a number: ";
  int choice;
  cin >> choice;

  while (find(available_numbers.begin(), available_numbers.end(), choice) == available_numbers.end())
  {
    cout << "Invalid choice. Try again: ";
    cin >> choice;
  }

  numbers.erase(find(numbers.begin(), numbers.end(), choice));

  this->symbol = choice;
}

template <typename T>

Tic_random_player<T>::Tic_random_player(T symbol,vector<int>nums) : RandomPlayer<T>(symbol),numbers(nums){
  this->name = "Random Computer Player";
  srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Tic_random_player<T>::getmove(int &x, int &y)
{
  vector<int> available_numbers = numbers; 
  if (available_numbers.empty())
  {
    cout << "No more numbers available for " << this->name << ". Skipping move.\n";
    return void();
  }

  int choice = available_numbers[rand() % available_numbers.size()];

  this->symbol = choice;

  numbers.erase(find(numbers.begin(), numbers.end(), choice));

  x = rand() % 3;
  y = rand() % 3;
}
