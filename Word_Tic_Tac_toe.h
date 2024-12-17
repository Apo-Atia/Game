#ifndef _WORD_TIC_TAC_TOE_H
#define _WORD_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
using namespace std;

class WordTicTacToe : public Board<char>
{
private:
    int rows, columns;
    set<string> dictionary; 

   
    bool check_word(int x, int y, int dx, int dy, string &formed_word)
    {
        formed_word = "";
        for (int i = 0; i < 3; ++i)
        {
            if (x >= 0 && x < rows && y >= 0 && y < columns)
                formed_word += board[x][y];
            x += dx;
            y += dy;
        }
        return dictionary.count(formed_word) > 0;
    }


    void load_words_from_file(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return;
        }

        string word;
        while (file >> word)
        {
            dictionary.insert(word);
        }

        file.close();
    }

public:
   
    WordTicTacToe(const string &filename) : rows(3), columns(3)
    {
        board = new char *[rows];
        for (int i = 0; i < rows; i++)
        {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++)
                board[i][j] = ' '; 
        }

        
        load_words_from_file(filename);
    }

   
    ~WordTicTacToe()
    {
        for (int i = 0; i < rows; ++i)
            delete[] board[i];
        delete[] board;
    }

    
    bool update_board(int x, int y, char symbol) override
    {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != ' ')
            return false; 

        board[x][y] = symbol;
        n_moves++;
        return true;
    }

  
    void display_board() override
    {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << " " << board[i][j] << " ";
                if (j < columns - 1)
                    cout << "|";
            }
            cout << "\n";
            if (i < rows - 1)
                cout << "-----------\n";
        }
    }


    bool is_win() override
    {
        string word;

        
        for (int i = 0; i < rows; ++i)
            if (check_word(i, 0, 0, 1, word))
                return true;

      
        for (int i = 0; i < columns; ++i)
            if (check_word(0, i, 1, 0, word))
                return true;

      
        if (check_word(0, 0, 1, 1, word) || check_word(0, columns - 1, 1, -1, word))
            return true;

        return false;
    }

  
    bool is_draw() override
    {
        return (n_moves == rows * columns && !is_win());
    }

    bool game_is_over() override
    {
        return is_win() || is_draw();
    }
};


template <typename T>
class WordPlayer : public Player<T>
{
public:
    WordPlayer(const string &name, T symbol);

    void getmove(int &x, int &y);
};


template <typename T>
WordPlayer<T>::WordPlayer(const string &name, T symbol):Player<T>(name, ' '){}

template <typename T>
void WordPlayer<T>::getmove(int &x, int &y) {
    int cell;
    char ch;
    cout << this->getname()<< ", enter your move (cell number 1-9 and a character): ";
    cin >> cell >> ch;
    x = (cell - 1) / 3;
    y = (cell - 1) % 3;
    this->symbol= toupper(ch);



}

template <typename T>
class Word_Random_Player : public RandomPlayer<T>
{
public:
    Word_Random_Player(T symbol) ;

    void getmove(int &x, int &y) override;
};

template<typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol): RandomPlayer<T>(symbol) {}

template <typename T>
void Word_Random_Player<T>::getmove(int &x, int &y) {
    int cell = rand() % 9 + 1;
    char ch = 'A' + (rand() % 26);
    x = (cell - 1) / 3;
    y = (cell - 1) % 3;
    cout << "AI chooses: cell " << cell << " with character '" << ch << "'\n";
    this->symbol=ch;
}

#endif

