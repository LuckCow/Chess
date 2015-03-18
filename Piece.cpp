#include "Piece.h"
#include <iostream>
using namespace std;

const int pawn = 100;
const int bishop = 305;
const int knight = 300;
const int rook = 500;
const int queen = 900;
const int king = 2000;

Piece::Piece(){cerr << "default constructor is not supposed to be called" << endl;} //it seems like this default constructor needs to exist...

Piece::Piece(int startRow, int startColumn, int pieceVal){

    row = startRow;
    column = startColumn;
    hasMoved = false;
    pointVal  = pieceVal;
    return;
} //second constructor creates new piece

Piece::~Piece(){
    //cout << "Piece destroyed!" << endl;
    return;
}

void Piece::SetPossibleMoves(int passdRow, int col, bool setVal = 1){
    if(passdRow >= 0 && passdRow <= 7 && col >= 0 && col <= 7){
        possibleMoves.theArray[passdRow][col] = setVal;
    } else {
        cout << "Error in Piece::SetPossibleMoves() range. " << endl;
    }
    return;
}


void Piece::EmptyPossibleMoves(){
    for(int loopRow = 0; loopRow <= 7; loopRow ++){
        for(int loopCol = 0; loopCol <= 7; loopCol ++){
            possibleMoves.theArray[loopRow][loopCol] = 0;
            }
        }

    return;
}


//This moves the piece by changing its location in the piece object, its location on the board is changed in the board move function
void Piece::MovePiece(int endRow, int endColumn){
        row = endRow;
        column = endColumn;
        hasMoved = true;
    return;
}

void Piece::PawnPromotion(){
    char promotionPiece = 'q';
    if(this->GetRow() == 7 && this->GetPointVal() == pawn){
        cout << "Enter piece type for pawn promotion (q, n, r, b): ";
        cin >> promotionPiece;
        switch(promotionPiece){
            case 'q':
                this->pointVal = queen;
                break;
            case 'n':
                this->pointVal = knight;
                break;
            case 'r':
                this->pointVal = rook;
                break;
            case 'b':
                this->pointVal = bishop;
                break;
        }
    }
    if(this->GetRow() == 0 && this->GetPointVal() == -pawn){
        cout << "Enter piece type for pawn promotion (q, n, r, b): ";
        cin >> promotionPiece;
        switch(promotionPiece){
            case 'q':
                this->pointVal = -queen;
                break;
            case 'n':
                this->pointVal = -knight;
                break;
            case 'r':
                this->pointVal = -rook;
                break;
            case 'b':
                this->pointVal = -bishop;
                break;
        }
    }
}


int Piece::GetRow() const{
    return row;
}
int Piece::GetColumn() const{
    return column;
}
int Piece::GetPointVal()const{
    return pointVal;
}
char Piece::GetDisplayLetter() const{
    char displayLetter;

    switch(pointVal){
        case 0:
            displayLetter = '-';
            break;
        case pawn:
            displayLetter = 'P';
            break;
        case bishop:
            displayLetter = 'B';
            break;
        case knight:
            displayLetter = 'N';
            break;
        case rook:
            displayLetter = 'R';
            break;
        case queen:
            displayLetter = 'Q';
            break;
        case king:
            displayLetter = 'K';
            break;
        case -pawn:
            displayLetter = 'p';
            break;
        case -bishop:
            displayLetter = 'b';
            break;
        case -knight:
            displayLetter = 'n';
            break;
        case -rook:
            displayLetter = 'r';
            break;
        case -queen:
            displayLetter = 'q';
            break;
        case -king:
            displayLetter = 'k';
            break;

    }

    return displayLetter;
}
string Piece::GetPieceName() const{
    string pieceName;
        switch(pointVal){
        case 0:
            pieceName = "empty";
            break;
        case pawn:
            pieceName = "Pawn";
            break;
        case bishop:
            pieceName = "Bishop";
            break;
        case knight:
            pieceName = "Knight";
            break;
        case rook:
            pieceName = "Rook";
            break;
        case queen:
            pieceName = "Queen";
            break;
        case king:
            pieceName = "King";
            break;
        case -pawn:
            pieceName = "Pawn";
            break;
        case -bishop:
            pieceName = "Bishop";
            break;
        case -knight:
            pieceName = "knight";
            break;
        case -rook:
            pieceName = "rook";
            break;
        case -queen:
            pieceName = "queen";
            break;
        case -king:
            pieceName = "king";
            break;

    }
    return pieceName;
}

bool Piece::GetHasMoved() const{
    return hasMoved;
}

bool Piece::CheckMove(int moveRow, int moveColumn) const{
    return possibleMoves.theArray[moveRow][moveColumn];
}

void Piece::PrintPieceInfo() const{
    cout << "The information about that piece is: " << endl;
    cout <<"row: " << GetRow() << endl;
    cout <<"column: " << GetColumn() << endl;
    cout <<"pointVal: " << GetPointVal() << endl;
    cout <<"displayLetter: " << GetDisplayLetter() << endl;
    cout <<"pieceName: " << GetPieceName() << endl;
    cout <<"hasMoved: " << GetHasMoved() << endl;
    cout <<"possibleMoves: " << endl;
    PrintPossibleMoves();
    return;
}


void Piece::PrintPossibleMoves() const{
    for (int i = 7; i >= 0; i--){
        cout << endl;
        for (int k = 0; k < 8; k++){
            cout << " " << possibleMoves.theArray[i][k] << " ";
        }
    }
    cout << endl << endl;

    return;
}
