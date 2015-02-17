
#include "Piece.h"
#include "Board.h"
using namespace std;

const int pawn = 100;
const int bishop = 305;
const int knight = 300;
const int rook = 500;
const int queen = 900;
const int king = 2000;

/**
void Piece::PoulatePossibleMoves(){
    int startRow, startColumn;

    switch(pointVal){
        case 0:
            //no possible moves
            break;
        case pawn:
            //
            break;
        case -pawn:
            break;
        case bishop:
        case -bishop:
            //
            break;
        case knight:
        case -knight:
            //
            break;
        case rook:
        case -rook:
            GenerateRookMoves();
            break;
        case queen:
        case -queen:
            //
            break;
        case king:
        case -king:
            //
            break;
    }
    return;

}

void Piece::GenerateRookMoves(){
    bool collisionFlag = false;
    for(int loopRow = 0; loopRow <= 7; loopRow ++){
        if(loopRow != row){
           possibleMoves.theArray[loopRow][column] = 1;
                }
        else if(loopRow == row){
            for(int loopCol = 0; loopCol <= 7; loopCol ++){
                if(loopCol != column){
                    possibleMoves.theArray[loopRow][loopCol] = 1;
                }
            }
        }
    }
    return;
} */

/** Checking collisions: needs whitePiece, blackPiece information, as well as the turn/ color of piece*/


/// I dont think i need these anymore vvvvvv
string Piece::GetStartSquare(string moveCommand) const{
    string startSquare;
    startSquare = moveCommand.substr(0,2);
    return startSquare;
}
string Piece::GetEndSquare(string moveCommand)const{
    string endSquare;
    endSquare = moveCommand.substr(2,2);
    return endSquare;
}

int Piece::GetSquareFile(string squareName)const{ //Files are letters (a-h)
    int file;
    file = squareName.at(0) - 'a'; //Converts ASCII to 0-7 for board[][]
    return file;
}
int Piece::GetSquareRank(string squareName)const{ //Ranks are numbers (1-8)
    int boardRank;
    boardRank = squareName.at(1) - '1';
    return boardRank;
}

