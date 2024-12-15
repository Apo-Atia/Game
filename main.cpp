#include <iostream>
#include "BoardGame_Classes.h"
#include "Pyramid_Tic_Tac_Toe.h"

using namespace std;
int main() {
    int choice;
    Player<char>* players[2];
    PyramidBoard<char>* pyramidBoard = new PyramidBoard<char>();
    string player1Name, player2Name;
    char symbol1;

    cout << "Welcome to Pyramid Tic-Tac-Toe!\n";

    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";

    cin >> choice;

    if (choice == 1) {
        cout << "Enter Player 1 name: ";
        cin.ignore();
        getline(cin,player1Name);
        cout<<"Choose symbol(X or O): ";
        cin>> symbol1;
        players[0] = new PyramidPlayer<char>(player1Name, symbol1);
    } else if (choice == 2) {
        cout<<"Choose symbol(X or Y): ";
        cin>> symbol1;
        players[0] = new Pyramid_Random_Player<char>(symbol1);
    } else {
        cout << "Invalid choice for Player 1. Exiting...\n";
        return 1;
    }



    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        if (towupper(symbol1)=='X'){
            players[1] = new PyramidPlayer<char>(player2Name, 'O');
        }
        else{
            players[1] = new PyramidPlayer<char>(player2Name, 'X');
        }

    } else if (choice == 2) {
        if (towupper(symbol1)=='X'){
            players[1] = new Pyramid_Random_Player<char>('O');
        }
        else{
            players[1] = new Pyramid_Random_Player<char>('X');
        }

    } else {
        cout << "Invalid choice for Player 2. Exiting...\n";
        return 1;
    }


    GameManager<char> pyramidGame(pyramidBoard, players);
    pyramidGame.run();


    delete pyramidBoard;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}


