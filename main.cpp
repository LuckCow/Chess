/** Object Oriented Chess
Author: Nick Collins
Created in 2015

The Board is an object, containing Piece Objects
*/


#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<cmath>
#include "Board.h"
#include "Piece.h"

using namespace std;
void menu(Board currentBoard);



int main()
{
    Board currentBoard;

    cout << "Welcome to Object Oriented Chess!" << endl << endl;
    currentBoard.PrintBoard();

    menu(currentBoard);

    return 0;
}

void menu(Board currentBoard){ //FIXME:: implement commands
    /**
    Commands:
        //quit
        help
        //print - prints board
        //printstate - prints board state
        reset
        surrender
        //(getPiece) e2
        //(move) e2e4
        //test - resets board to test board

    */


    string userInput;
    while(userInput != "q"){
        getline (cin, userInput);

        if(userInput == "q" || userInput == "quit"){
            break;
        }
        if(userInput == "print"){
            currentBoard.PrintBoard();
        }
        else if(userInput == "printstate" || userInput == "prints"){
            currentBoard.PrintBoardState();
        }
        else if(userInput == "test"){
            currentBoard.ResetTestBoard();
            currentBoard.PrintBoard();
        }
        else if(userInput == "white"){
            currentBoard.PrintPieceVector(1);
            cout << "White moves: " << endl;
            currentBoard.PrintColorMoves(1);
        }
        else if(userInput == "black"){
            currentBoard.PrintPieceVector(0);
            cout << "Black moves: " << endl;
            currentBoard.PrintColorMoves(0);
        }
        else if(userInput.length() == 4){//FIXME: add range validation
        currentBoard.MovePiece(userInput);
        }
        else if(userInput.length() == 2){//FIXME: add range validation

        (currentBoard.GetPiece(currentBoard.GetSquareRank(userInput),currentBoard.GetSquareFile(userInput)))->PrintPieceInfo();
        }
    }

}

