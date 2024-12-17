#include "BoardGame_Classes.h"
#include "connect_four.h"
#include "Misere_Tic_Tac_Toe.h"
#include "Pyramid_Tic_Tac_Toe.h"
#include "Tic_Tac_Toe4x4.h"
#include "Tic_Tac_Toe5x5.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include "Word_Tic_Tac_toe.h"
#include "numerical_Tic.h"
#include<iostream>
using namespace std;

void Pyramic_Tic()
{
    int choice;
    Player<char>* players[2];
    PyramidBoard<char>* pyramidBoard = new PyramidBoard<char>();
    string player1Name, player2Name;
    char symbol1;

    cout << "Welcome to Pyramid Tic-Tac-Toe!\n";

    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";

    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Player 1 name: ";
        cin.ignore();
        getline(cin, player1Name);
        cout << "Choose symbol(X or O): ";
        cin >> symbol1;
        players[0] = new PyramidPlayer<char>(player1Name, symbol1);
    }
    else if (choice == 2)
    {
        cout << "Choose symbol(X or Y): ";
        cin >> symbol1;
        players[0] = new Pyramid_Random_Player<char>(symbol1);
    }
    else
    {
        cout << "Invalid choice for Player 1. Exiting...\n";
        return;
    }

    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        if (towupper(symbol1) == 'X')
        {
            players[1] = new PyramidPlayer<char>(player2Name, 'O');
        }
        else
        {
            players[1] = new PyramidPlayer<char>(player2Name, 'X');
        }
    }
    else if (choice == 2)
    {
        if (towupper(symbol1) == 'X')
        {
            players[1] = new Pyramid_Random_Player<char>('O');
        }
        else
        {
            players[1] = new Pyramid_Random_Player<char>('X');
        }
    }
    else
    {
        cout << "Invalid choice for Player 2. Exiting...\n";
        return;
    }

    GameManager<char> pyramidGame(pyramidBoard, players);
    pyramidGame.run();

    delete pyramidBoard;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}
void Connect_four()
{
    int choice;
    Player<char>* players[2];
    connect_four<char>* B = new connect_four<char>(); // Connect Four-specific board
    string player1Name, player2Name;

    cout << "Welcome to FCAI Connect Four Game! :D\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            players[0] = new connect_four_player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new connect_four_Random_player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            players[1] = new connect_four_player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new connect_four_Random_player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }


    GameManager<char> connect_four_game(B, players);
    connect_four_game.run();


    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}
void Tic_5()
{
    int choice;
    Player<char>* players[2];
    Tic_Tac_Toe5x5_Board<char>* board = new Tic_Tac_Toe5x5_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to FCAI TicTacToe 5x5 Game. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            players[0] = new TicTacToe5x5_Player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new TicTacToe5x5_RandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            players[1] = new TicTacToe5x5_Player<char>(player2Name, 'o');
            break;
        case 2:
            players[1] = new TicTacToe5x5_RandomPlayer<char>('o');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    GameManager<char> game(board, players);
    game.run();

    delete board;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

void Word_Tic()
{
    int choice;
    Player<char>* players[2];
    WordTicTacToe* wordBoard = new WordTicTacToe("dic.txt");
    string player1Name, player2Name;

    cout << "Welcome to Word Tic-Tac-Toe!\n";

    // Player 1 setup
    cout << "Is Player 1 human or AI? (1: Human, 2: AI): ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Player 1 name: ";
        cin.ignore();
        getline(cin, player1Name);
        players[0] = new WordPlayer<char>(player1Name, ' ');
    }
    else
    {
        players[0] = new Word_Random_Player<char>(' ');
    }


    cout << "Is Player 2 human or AI? (1: Human, 2: AI): ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Player 2 name: ";
        cin.ignore();
        getline(cin, player2Name);
        players[1] = new WordPlayer<char>(player2Name, ' ');
    }
    else
    {
        players[1] = new Word_Random_Player<char>(' ');
    }

    GameManager<char> wordGame(wordBoard, players);
    wordGame.run();


    delete players[0];
    delete players[1];
    delete wordBoard;
}

void numerical_Tic()
{
    srand(static_cast<unsigned int>(time(0)));
    int choice;
    Player<int>* players[2];
    Tic_board<int>* B = new Tic_board<int>();
    string player1Name, player2Name;

    cout << "Welcome to the Tic-Tac-Toe game! :)\n";


    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            players[0] = new Tic_player<int>(player1Name, 1, { 1, 3, 5, 7, 9 });
            break;
        case 2:
            players[0] = new Tic_random_player<int>(1, { 1, 3, 5, 7, 9 });
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }


    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
            players[1] = new Tic_player<int>(player2Name, 2, { 2, 4, 6, 8 });
            break;
        case 2:
            players[1] = new Tic_random_player<int>(2, { 2, 4, 6, 8 });
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }


    GameManager<int> tic_game(B, players);
    tic_game.run();


    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

void Misere_Tic()
{
    int choice;
    Player<char>* players[2];
    Misere_Tic_Tac_Toe_Board<char>* board = new Misere_Tic_Tac_Toe_Board<char>();

    cout << "Welcome to FCAI Misere Tic Tac Toe Game. :)\n";


    cout << "Enter Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new Misere_Tic_Tac_Toe_Player<char>("Player O ", 'X');
            break;
        case 2:
            players[0] = new Misere_Tic_Tac_Toe_RandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            delete board;
            return;
    }


    cout << "Enter Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new Misere_Tic_Tac_Toe_Player<char>("Player X ", 'o');
            break;
        case 2:
            players[1] = new Misere_Tic_Tac_Toe_RandomPlayer<char>('o');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            delete players[0];
            delete board;
            return;
    }


    GameManager<char> game(board, players);
    game.run();


    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Tic_4()
{
    int choice;
    Player<char>* players[2];
    Tic_Tac_Toe4x4_Board<char>* board = new Tic_Tac_Toe4x4_Board<char>();

    cout << "Welcome to FCAI 4x4 Tic Tac Toe Game. :)\n";


    cout << "Enter Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new Tic_Tac_Toe4x4_Player<char>("Player X ", 'X');
            break;
        case 2:
            players[0] = new Tic_Tac_Toe4x4_RandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            delete board;
            return;
    }


    cout << "Enter Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new Tic_Tac_Toe4x4_Player<char>("Player O ", 'o');
            break;
        case 2:
            players[1] = new Tic_Tac_Toe4x4_RandomPlayer<char>('o');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            delete players[0];
            delete board;
            return;
    }


    GameManager<char> game(board, players);
    game.run();


    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
void Ultimate_Tic()
{
    int choice;
    Player<char>* players[2];
    UltimateBoard<char>* ultimateBoard = new UltimateBoard<char>();
    string player1Name, player2Name;
    char symbol1;

    cout << "Welcome to Ultimate Tic-Tac-Toe!\n";

    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Player 1 name: ";
        cin.ignore();
        getline(cin, player1Name);
        cout << "Choose symbol (X or O): ";
        cin >> symbol1;
        players[0] = new UltimatePlayer<char>(player1Name, toupper(symbol1));
    }
    else if (choice == 2)
    {
        cout << "Choose symbol (X or O): ";
        cin >> symbol1;
        players[0] = new Ultimate_Random_Player<char>(toupper(symbol1));
    }
    else
    {
        cout << "Invalid choice for Player 1. Exiting...\n";
        delete ultimateBoard;
        return;
    }

    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Player 2 name: ";
        cin.ignore();
        getline(cin, player2Name);
        if (toupper(symbol1) == 'X')
        {
            players[1] = new UltimatePlayer<char>(player2Name, 'O');
        }
        else
        {
            players[1] = new UltimatePlayer<char>(player2Name, 'X');
        }
    }
    else if (choice == 2)
    {
        if (toupper(symbol1) == 'X')
        {
            players[1] = new Ultimate_Random_Player<char>('O');
        }
        else
        {
            players[1] = new Ultimate_Random_Player<char>('X');
        }
    }
    else
    {
        cout << "Invalid choice for Player 2. Exiting...\n";
        delete ultimateBoard;
        return;
    }

    GameManager<char> ultimateGame(ultimateBoard, players);
    ultimateGame.run();

    delete ultimateBoard;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

int main()
{
    int choice;

    while (true)
    {

        cout << " Welcome To F-CAI Games board\n ";
        cout << "choose game you want\n\n ";
        cout << "1- for Pyramic_Tic\n ";
        cout << "2- for Connect_four\n ";
        cout << "3- for Tic_5\n ";
        cout << "4- for Word_Tic\n ";
        cout << "5- for numerical_Tic\n ";
        cout << "6- for Misere_Tic\n ";
        cout << "7- for Tic_4\n ";
        cout << "8- for Ultimate_Tic\n ";
        cout << "0- for exit\n ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                Pyramic_Tic();
                break;
            case 2:
                Connect_four();
                break;
            case 3:
                Tic_5();
                break;
            case 4:
                Word_Tic();
                break;
            case 5:
                numerical_Tic();
                break;
            case 6:
                Misere_Tic();
                break;
            case 7:
                Tic_4();
                break;
            case 8:
                Ultimate_Tic();
                break;
            case 0:
                return 0;
            default:
                cout << "invalid choice try again:\n";
                break;
        }
    }
}
