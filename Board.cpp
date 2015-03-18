/*  Board.cpp



*/


#include <iostream>
#include <vector>
#include "Board.h"
#include "Piece.h"
using namespace std;

const int pawn = 100;
const int bishop = 305;
const int knight = 300;
const int rook = 500;
const int queen = 900;
const int king = 2000;
const int ASCII_1 = 49;
const int ASCII_8 = 56;
const int ASCII_a = 97;
const int ASCII_h = 104;

const int startingBoard[8][8] = { {rook, knight, bishop, queen, king, bishop, knight, rook},
                            {pawn,pawn,pawn,pawn,pawn,pawn, pawn, pawn},
                            {0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0},
                            {-pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn},
                            {-rook, -knight, -bishop, -queen, -king, -bishop, -knight, -rook}};

        //testBoard is changed manually in source code for testing
const int testBoard[8][8] = { {king, 0, rook, 0, 0, 0, 0, 0},
                              {0, 0, king, 0, 0, 0, 0, 0},
                              {0, 0, 0, bishop, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, -bishop, 0, 0},
                              {0, 0, 0, knight, 0, 0, 0, 0},
                              {0, 0, 0, -king, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}  };

Board::Board(){ //constructor
    cout << "Default Constructor Called" << endl;
    for (int i = 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
            board[i][j] = new Piece(i,j,startingBoard[i][j]); //setup starting position
            }
    }
    turn = true;
    PopulateBitBoard(0);
    PopulateBitBoard(1);
    PopulatePieceVector(1);
    PopulatePieceVector(0);
    whiteKing = &board[0][4];
    blackKing = &board[7][4];
    whiteCheck = 0;
    blackCheck = 0;

    PopulateAllMoves(false);

    ListColorMoves(1);
    ListColorMoves(0);

    return;
}

Board::Board(const Board& origBoard){ //Copy Constructor
    cout << "Copy Constructor Called" << endl;
    for (int i = 0; i < 8; i++){
            cout << "Copy constructor loop i: " << i << endl;
        for (int j = 0; j < 8; j++){
            cout << "Copy constructor loop j: " << j << endl;
            board[i][j] = (origBoard.GetPiece(i,j)); //Copy Pieces based on values
        }
    }
    cout << "Out of Loop CConstructor" << endl;
    turn = origBoard.turn;
    PopulateBitBoard(0);
    PopulateBitBoard(1);
    PopulatePieceVector(1);
    PopulatePieceVector(0);
    whiteKing = origBoard.whiteKing;
    blackKing = origBoard.blackKing;
    whiteCheck = origBoard.whiteCheck;
    blackCheck = origBoard.blackCheck;

    PopulateAllMoves(true);

    ListColorMoves(1);
    ListColorMoves(0);

    return;
}

//Resets the board for a new game
void Board::ResetBoard(){
    for (int i = 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
            board[i][j] = new Piece(i,j,startingBoard[i][j]); //setup starting position
            }
    }
    turn = true;
    PopulateBitBoard(0);
    PopulateBitBoard(1);

    PopulateAllMoves(false);
    return;
}

void Board::ResetTestBoard(){
    for (int i = 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
            delete board[i][j];
            }
    }
    for (int i = 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
            board[i][j] = new Piece(i,j,testBoard[i][j]); //setup starting position
            }
    }
    turn = true;
    PopulateBitBoard(0);
    PopulateBitBoard(1);
    PopulateAllMoves(true);
    return;
}


void Board::PrintBoard() const{ //FIXME:: add A-H and 1-8 on side, and flip board for black's turn

    for (int i = 7; i >= 0; i--){  // we must iterate the ranks down from 7 to 0 otherwise the board will be upside down
        cout << endl;
        for (int k = 0; k < 8; k++){
            cout << " " << GetPiece(i,k)->GetDisplayLetter() << " ";
        }
    }
 cout << endl << endl;
    return;
}

void Board::PrintBoardState() const{
    PrintBoard();
    cout << endl;
    cout << "Turn: " << turn << " (1 is White, 0 is Black)" << endl;
    cout << "whitePieces: " << endl;
    PrintBitBoard(1);
    cout << endl;
    cout << "blackPieces: " << endl;
    PrintBitBoard(0);
    cout << endl;
    return;
}

bool Board::GetTurn() const{
    return turn;
}

Piece* Board::GetPiece(int row/*[rank]*/, int column/*[file]*/) const{
    return board[row][column];
}

int Board::GetPieceVal(int row, int column) const{
    return board[row][column]->GetPointVal();
}


void Board::PopulateBitBoard(bool color){
    if(color){ //white
        for(int row = 0; row <= 7; row++){
            for(int column = 0; column <= 7; column++){
                if(GetPieceVal(row, column) > 0){
                    whiteBitBoard[row][column] = 1;
                }
                else {
                    whiteBitBoard[row][column] = 0;
                }
            }
        }
    }
    else{ //black
        for(int row = 0; row <= 7; row++){
            for(int column = 0; column <= 7; column++){
                if(GetPieceVal(row, column) < 0){
                    blackBitBoard[row][column] = 1;
                }
                else {
                    blackBitBoard[row][column] = 0;
                }
            }
        }
    }
    return;
}

void Board::PrintBitBoard(bool color)const{
    if(color){
    for (int i = 7; i >= 0; i--){  // we must iterate the ranks down from 7 to 0 otherwise the board will be upside down
        cout << endl;
        for (int k = 0; k < 8; k++){
            cout << " " << whiteBitBoard[i][k] << " ";
        }
    }
    cout << endl << endl;
    }
    else{
    for (int i = 7; i >= 0; i--){  // we must iterate the ranks down from 7 to 0 otherwise the board will be upside down
        cout << endl;
        for (int k = 0; k < 8; k++){
            cout << " " << blackBitBoard[i][k] << " ";
        }
    }
    cout << endl << endl;
    }

    return;
}

bool Board::GetBitBoard(int row, int column, bool color) const{
    if(color){
        return whiteBitBoard[row][column];
    }
    else{
        return blackBitBoard[row][column];
    }
}

void Board::SetCheck(bool color){
    int kingRow;
    int kingColumn;
    if(color){ //white check
        kingRow = (*whiteKing)->GetRow(); //Get King Square
        kingColumn = (*whiteKing)->GetColumn();
        if(DetectAttack(kingRow, kingColumn, color)){
            whiteCheck = true;
        } else{
            blackCheck = false;
        }
        //See if enemy pieces can move on king square
            //if so, then king is in check
    } else{
        kingRow = (*blackKing)->GetRow(); //Get King Square
        kingColumn = (*blackKing)->GetColumn();
        if(DetectAttack(kingRow, kingColumn, color)){
            blackCheck = true;
        } else{
            blackCheck = false;
        }
    }
    return;
}

bool Board::GetCheck(bool color) const{
    if(color){
        return whiteCheck;
    } else{
        return blackCheck;
    }
}

//Not fully tested
bool Board::DetectAttack(int sqRow, int sqCol, bool color){ //Look for all pieces attacking a square
    bool isAttacked = false;
    if(color){ //white under attack from black pieces
        //Go through vector of black pieces and look at where or not they attack the square in question
        for(unsigned int i = 0; i < blackPieces.size(); i++){
            if( (*blackPieces.at(i))->CheckMove(sqRow, sqCol) ){
                isAttacked = true;
                break;
            }
        }
    }
    else{
        for(unsigned int i = 0; i < whitePieces.size(); i++){
            if( (*whitePieces.at(i))->CheckMove(sqRow, sqCol) ){
                isAttacked = true;
                break;
            }
        }
    }
    return isAttacked;
}



void Board::PopulatePieceVector(bool color){
    if(color){
        for(int row = 0; row <= 7; row++){
            for(int col = 0; col <= 7; col++){
                if(board[row][col]->GetPointVal() > 0){
                    whitePieces.push_back(&board[row][col]);
                }
            }
        }
    }
    else{
        for(int row = 0; row <= 7; row++){
            for(int col = 0; col <= 7; col++){
                if(board[row][col]->GetPointVal() < 0){
                    blackPieces.push_back(&board[row][col]);
                }
            }
        }
    }

    return;
}

void Board::PrintPieceVector(bool color) const{
    if(color){
        cout << "White pieces: " << endl;
        for(unsigned int i=0; i < whitePieces.size(); i++){
            cout << i + 1 << ": " << (*whitePieces.at(i))->GetPieceName()
                 << " at row: " << (*whitePieces.at(i))->GetRow()
                 << " column: " << (*whitePieces.at(i))->GetColumn()  <<  endl;
        }
    }
    else{
       cout << "Black pieces: " << endl;
        for(unsigned int i=0; i < blackPieces.size(); i++){
            cout << i + 1 << ": " << (*blackPieces.at(i))->GetPieceName()
                 << " at row: " << (*blackPieces.at(i))->GetRow()
                 << " column: " << (*blackPieces.at(i))->GetColumn()  <<  endl;
        }
    }
    return;
}

void Board::PopulateAllMoves(bool check){ //Check parameter determines if the possible moves should be limited by King's vulnerability (acts recursively)
    for (int i = 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
            PopulatePossibleMoves(GetPiece(i,j), check); //Kings are still checked in here
            }
    }
    PopulatePossibleMoves(*whiteKing, check);
    PopulatePossibleMoves(*blackKing, check);

    return;
}

void Board::ListColorMoves(bool color){
    vector<int> vectorMove;
    if(color){
        for(unsigned int v = 0; v < whitePieces.size(); v++){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if((*(whitePieces.at(v)))->CheckMove(i,j)){
                        vectorMove.push_back((*whitePieces.at(v))->GetRow());
                        vectorMove.push_back((*whitePieces.at(v))->GetColumn());
                        vectorMove.push_back(i);
                        vectorMove.push_back(j);
                        whiteMoves.push_back(vectorMove);
                        vectorMove.clear();
                    }
                }
            }
        }
    } else{
        for(unsigned int v = 0; v < blackPieces.size(); v++){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    if((*(blackPieces.at(v)))->CheckMove(i,j)){
                        vectorMove.push_back((*blackPieces.at(v))->GetRow());
                        vectorMove.push_back((*blackPieces.at(v))->GetColumn());
                        vectorMove.push_back(i);
                        vectorMove.push_back(j);
                        blackMoves.push_back(vectorMove);
                        vectorMove.clear();
                    }
                }
            }
        }
    }
    return;
}

int Board::MoveVectorToInt(int v, bool color){ //
    int moveInt = 0;
    if(color){
        moveInt += 1000 * (whiteMoves.at(v).at(0) + 1);
        moveInt += 100 * (whiteMoves.at(v).at(1) + 1);
        moveInt += 10 * (whiteMoves.at(v).at(2) + 1);
        moveInt += 1 * (whiteMoves.at(v).at(3) + 1);
    } else{
        moveInt += 1000 * (blackMoves.at(v).at(0) + 1);
        moveInt += 100 * (blackMoves.at(v).at(1) + 1) ;
        moveInt += 10 * (blackMoves.at(v).at(2) + 1);
        moveInt += 1 * (blackMoves.at(v).at(3) + 1);
    }
    return moveInt;
}

void Board::PrintColorMoves(bool color){
    if(color){
        cout << "White has " << whiteMoves.size() << " moves: " << endl;
        for(unsigned int v = 0; v < whiteMoves.size(); v++){
            cout << v + 1 << ": " << MoveVectorToInt(v,1) << endl;
            }

    } else{
        cout << "Black has " << blackMoves.size() << " moves: " << endl;
        for(unsigned int v = 0; v < blackMoves.size(); v++){
            cout << v + 1 << ": " << MoveVectorToInt(v,0) << endl;
            }

    }
    return;
}

void Board::PopulatePossibleMoves(Piece* piecePtr, bool check){
    if(piecePtr->GetPointVal() == 0){
        return;
    }
    piecePtr->EmptyPossibleMoves();
    switch(piecePtr->GetPointVal()){
        case pawn:
        case -pawn:
            GeneratePawnMoves(piecePtr);
            break;
        case bishop:
        case -bishop:
            GenerateBishopMoves(piecePtr);
            break;
        case knight:
        case -knight:
            GenerateKnightMoves(piecePtr);
            break;
        case rook:
        case -rook:
            GenerateRookMoves(piecePtr);
            break;
        case queen:
        case -queen:
            GenerateBishopMoves(piecePtr);
            GenerateRookMoves(piecePtr);
            break;
        case king:
        case -king:
            GenerateKingMoves(piecePtr);
            break;
    }
    if(check){
        GenerateCheckMoves(piecePtr);
    }

    return;

}


void Board::GenerateCheckMoves(Piece* piecePtr){
    /* Check what pieces are attacking the king
        moves are only possible if
            -a piece blocks the check,
            -the king moves out of the way from the check,
            -or capture the piece doing the checking
        Also:
        Any move that results in the king's capture is illegal (pins to king)

        Get all moves,
        perform moves on copy of board, check resulting board for check,
            if still check, the move is impossible
    */
    /*
    New plan: After generating the moves of a particular piece, go th
    */

    Board game = *this; //Make Copy constructor
    int startRow = piecePtr->GetRow();
    int startCol = piecePtr->GetColumn();
    Piece* gamePiecePtr = game.board[startRow][startCol];
    bool currentTurn = this->GetTurn();

    if((piecePtr->GetPointVal() > 0 && currentTurn) || (piecePtr->GetPointVal() < 0 && !currentTurn)){
    for(int row = 0; row <= 7; row++){
        for(int col = 0; col <= 7; col++){
            if(piecePtr->CheckMove(row, col) ){
                cout << "testing valid move " << piecePtr->GetPieceName() << " to row: " << row << " col: " << col << endl;
                if(!game.VirtualMovePiece(gamePiecePtr, row, col)){
                    piecePtr->SetPossibleMoves(row, col, 0);
                    cout << "Possible move removed due to resulting king vulnerability" << endl;
                }
                ///ISSUES
                //make temporary moveset, reset after Virtual Move populate            }
        }
    }
    }
    cout << "Done generating check moves" << endl;
    return;
}
}



void Board::GenerateRookMoves(Piece* piecePtr){
    bool pieceColor = true;
    if(piecePtr->GetPointVal() < 0){
        pieceColor = false;
    }

    /** Loops upward through columns */
    for(int loopRow = piecePtr->GetRow() + 1; loopRow <= 7; loopRow++){
        if(GetBitBoard(loopRow, piecePtr->GetColumn(), pieceColor)){ //If piece is friendly, rook cannot move there
            break; //Collision: no more moves in this path are avaible
        }
        else if(GetBitBoard(loopRow, piecePtr->GetColumn(), !pieceColor)){ //If piece is enemy, rook can move there
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn(), 1);
            break; //Collision: no more moves in this path are available
        }
        else{
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn(), 1); //If square is empty, rook can move there
        }
    }

    /** Loops downward through columns */
    for(int loopRow = piecePtr->GetRow() - 1; loopRow >= 0; loopRow--){
        if(GetBitBoard(loopRow, piecePtr->GetColumn(), pieceColor)){
            break;
        }
        else if(GetBitBoard(loopRow, piecePtr->GetColumn(), !pieceColor)){
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn(), 1);
            break;
        }
        else{
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn(), 1);
        }
    }

        //goes through rows
    /** Loops rightward through rows */
    for(int loopCol = piecePtr->GetColumn() + 1; loopCol <= 7; loopCol++){
        if(GetBitBoard(piecePtr->GetRow(), loopCol, pieceColor) ){
            break;
        }
        else if(GetBitBoard(piecePtr->GetRow(), loopCol, !pieceColor)){
            piecePtr->SetPossibleMoves(piecePtr->GetRow(), loopCol, 1);
            break;
        }
        else{
            piecePtr->SetPossibleMoves(piecePtr->GetRow(), loopCol, 1);
        }

    }
    /** Loops leftward through rows */
    for(int loopCol = piecePtr->GetColumn() - 1; loopCol >= 0; loopCol--){
        if(GetBitBoard(piecePtr->GetRow(), loopCol, pieceColor) ){
            break;
        }
        else if(GetBitBoard(piecePtr->GetRow(), loopCol, !pieceColor)){
            piecePtr->SetPossibleMoves(piecePtr->GetRow(), loopCol, 1);
            break;
        }
        else{
            piecePtr->SetPossibleMoves(piecePtr->GetRow(), loopCol, 1);
        }

    }

    return;
}

void Board::GenerateBishopMoves(Piece* piecePtr){
    bool pieceColor = true;
    if(piecePtr->GetPointVal() < 0){
        pieceColor = false;
    }
    int columnCounter;
    //Bishops move by doing multiples of theses:
    //rank + 1 && file +1
    //rank + 1 && file -1
    //rank - 1 && file -1
    //rank - 1 && file +1
    //in other words, the absolute value of the difference between the files and the difference between the ranks are equal

       /* if(abs(rankDifference) == abs(fileDifference)){

        //rank + 1 && file +1 -- up and to the right
        if(rankDifference > 0 && fileDifference > 0){
            for(int i = 1; i < fileDifference; i++){
                    currentRank++;
                    currentFile++;
                    bishopPath.push_back(board[currentRank][currentFile]);
                    //cout << "Found piece at rank " << currentRank << " and file " << currentFile << ": " << board[currentRank][currentFile] << endl; //for debugging
                }
            }
        }*/
    /** Loops upward and to the right */
    columnCounter = 1;
    for(int loopRow = piecePtr->GetRow() + 1; loopRow <= 7; loopRow++){
        if( (piecePtr->GetColumn() + columnCounter) > 7){
            break;
        }

        if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, pieceColor)){ //If piece is friendly, bishop cannot move there
            break; //Collision: no more moves in this path are avaible
        }
        else if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, !pieceColor)){ //If piece is enemy, bishop can move there
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1);
            break; //Collision: no more moves in this path are available
        }
        else{
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1); //If square is empty, bishop can move there
        }
        columnCounter += 1;
    }

    /** Loops upward and to the left
                +row            -column        */
    columnCounter = -1;
    for(int loopRow = piecePtr->GetRow() + 1; loopRow <= 7; loopRow++){
        if( (piecePtr->GetColumn() + columnCounter) < 0){
            break;
        }

        if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, pieceColor)){ //If piece is friendly, bishop cannot move there
            break; //Collision: no more moves in this path are avaible
        }
        else if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, !pieceColor)){ //If piece is enemy, bishop can move there
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1);
            break; //Collision: no more moves in this path are available
        }
        else{
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1); //If square is empty, bishop can move there
        }
        columnCounter -= 1;
    }
    /** Loops downward and to the left
                -row            -column        */
    columnCounter = -1;
    for(int loopRow = piecePtr->GetRow() - 1; loopRow >= 0; loopRow--){
        if( (piecePtr->GetColumn() + columnCounter) < 0){
            break;
        }

        if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, pieceColor)){ //If piece is friendly, bishop cannot move there
            break; //Collision: no more moves in this path are avaible
        }
        else if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, !pieceColor)){ //If piece is enemy, bishop can move there
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1);
            break; //Collision: no more moves in this path are available
        }
        else{
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1); //If square is empty, bishop can move there
        }
        columnCounter -= 1;
    }
    /** Loops downward and to the right
                -row            +column        */
    columnCounter = +1;
    for(int loopRow = piecePtr->GetRow() - 1; loopRow >= 0; loopRow--){
        if( (piecePtr->GetColumn() + columnCounter) > 7){
            break;
        }

        if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, pieceColor)){ //If piece is friendly, bishop cannot move there
            break; //Collision: no more moves in this path are avaible
        }
        else if(GetBitBoard(loopRow, piecePtr->GetColumn() + columnCounter, !pieceColor)){ //If piece is enemy, bishop can move there
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1);
            break; //Collision: no more moves in this path are available
        }
        else{
            piecePtr->SetPossibleMoves(loopRow, piecePtr->GetColumn() + columnCounter, 1); //If square is empty, bishop can move there
        }
        columnCounter += 1;
    }


    return;

}

void Board::GenerateKnightMoves(Piece* piecePtr){
    bool pieceColor = true;
    if(piecePtr->GetPointVal() < 0){
        pieceColor = false;
    }

    /*
    Knights move in an L shape
    either 2 files and 1 rank, or 1 file and 2 ranks
    */

    // Up/Down 1 and over 2
    for(int loopRow = (piecePtr->GetRow() - 1); loopRow <= (piecePtr->GetRow() + 1); loopRow += 2){
        for(int loopCol = (piecePtr->GetColumn() - 2); loopCol <= (piecePtr->GetColumn() + 2); loopCol += 4){
            if(loopRow <= 7 && loopRow >= 0 && loopCol <= 7 && loopCol >= 0 ){
                    if(!GetBitBoard(loopRow, loopCol, pieceColor)){
                            piecePtr->SetPossibleMoves(loopRow, loopCol, 1);
                    }
            }
        }
    }

    //up/down 1 and over 2
    for(int loopRow = (piecePtr->GetRow() - 2); loopRow <= (piecePtr->GetRow() + 2); loopRow += 4){
        for(int loopCol = (piecePtr->GetColumn() - 1); loopCol <= (piecePtr->GetColumn() + 1); loopCol += 2){
            if(loopRow <= 7 && loopRow >= 0 && loopCol <= 7 && loopCol >= 0 ){
                    if(!GetBitBoard(loopRow, loopCol, pieceColor)){
                            piecePtr->SetPossibleMoves(loopRow, loopCol, 1);
                    }
            }
        }
    }


    return;
}


void Board::GenerateKingMoves(Piece* piecePtr){ //FIXME: add castling & make sure king cannot move to where he can be captured
    bool pieceColor = true;
    if(piecePtr->GetPointVal() < 0){
        pieceColor = false;
    }

    //Regular King Moves - 1 square around king
    for(int loopRow = (piecePtr->GetRow() - 1); loopRow <= (piecePtr->GetRow() + 1); loopRow++){
        for(int loopCol = (piecePtr->GetColumn() - 1); loopCol <= (piecePtr->GetColumn() + 1); loopCol++){
            if(loopRow <= 7 && loopRow >= 0 && loopCol <= 7 && loopCol >= 0 ){
                    if(!GetBitBoard(loopRow, loopCol, pieceColor) && !DetectAttack(loopRow, loopCol, pieceColor) ){
                            piecePtr->SetPossibleMoves(loopRow, loopCol, 1);
                    }
            }
        }
    }
    piecePtr->SetPossibleMoves(piecePtr->GetRow(), piecePtr->GetColumn(), 0); //Remove the king's current square

    return;
}

void Board::GeneratePawnMoves(Piece* piecePtr){
    bool pieceColor = true;
    if(piecePtr->GetPointVal() < 0){
        pieceColor = false;
    }

    if(pieceColor){ //White Pawn

        // 2 squares on first move of pawn
        if(piecePtr->GetRow() == 1 && !GetBitBoard(2, piecePtr->GetColumn(), 1) && !GetBitBoard(2, piecePtr->GetColumn(), 0)){
            piecePtr->SetPossibleMoves(piecePtr->GetRow() + 2, piecePtr->GetColumn(), 1);
        }

        //Regular 1 square move
        if(!GetBitBoard(piecePtr->GetRow() + 1, piecePtr->GetColumn() , 1) && !GetBitBoard(piecePtr->GetRow() + 1, piecePtr->GetColumn(), 0)){
            piecePtr->SetPossibleMoves(piecePtr->GetRow() + 1, piecePtr->GetColumn(), 1);
        }

        //Capture
        if(GetBitBoard(piecePtr->GetRow() + 1, piecePtr->GetColumn() + 1, !pieceColor) && piecePtr->GetColumn() + 1 <= 7){ //Capture right
            piecePtr->SetPossibleMoves(piecePtr->GetRow() + 1, piecePtr->GetColumn() + 1, 1);
        }
        if(GetBitBoard(piecePtr->GetRow() + 1, piecePtr->GetColumn() - 1, !pieceColor) && piecePtr->GetColumn() - 1 >= 0){ //Capture left
            piecePtr->SetPossibleMoves(piecePtr->GetRow() + 1, piecePtr->GetColumn() - 1, 1);
        }
    }
    else{ //Black Pawn
        // 2 squares on first move of pawn
        if(piecePtr->GetRow() == 6 && !GetBitBoard(5, piecePtr->GetColumn(), 1) && !GetBitBoard(5, piecePtr->GetColumn(), 0)){
            piecePtr->SetPossibleMoves(piecePtr->GetRow() - 2, piecePtr->GetColumn(), 1);
        }

        //Regular 1 square move
        if(!GetBitBoard(piecePtr->GetRow() - 1, piecePtr->GetColumn() , 1) && !GetBitBoard(piecePtr->GetRow() - 1, piecePtr->GetColumn(), 0)){
            piecePtr->SetPossibleMoves(piecePtr->GetRow() - 1, piecePtr->GetColumn(), 1);
        }

        //Capture
        if(GetBitBoard(piecePtr->GetRow() - 1, piecePtr->GetColumn() + 1, !pieceColor) && piecePtr->GetColumn() + 1 <= 7){ //Capture right
            piecePtr->SetPossibleMoves(piecePtr->GetRow() - 1, piecePtr->GetColumn() + 1, 1);
        }
        if(GetBitBoard(piecePtr->GetRow() - 1, piecePtr->GetColumn() - 1, !pieceColor) && piecePtr->GetColumn() - 1 >= 0){ //Capture left
            piecePtr->SetPossibleMoves(piecePtr->GetRow() - 1, piecePtr->GetColumn() - 1, 1);
        }
    }

    return;
}


void Board::MovePiece(string moveCommand){
    string startSquare = GetStartSquare(moveCommand);
    string endSquare = GetEndSquare(moveCommand);
    int file1 = GetSquareFile(startSquare);
    int file2 = GetSquareFile(endSquare);
    int rank1 = GetSquareRank(startSquare);
    int rank2 = GetSquareRank(endSquare);
    Piece* movingPiece = GetPiece(rank1,file1);
    Piece* emptySquare = new Piece(rank1,file1,0);

    //   /*
    // Verifies that the correct color is moving on the correct turn
    if( !(turn && (movingPiece->GetPointVal() > 0) ) && !(!turn && (movingPiece->GetPointVal() < 0) ) ){
        cout << "Invalid move: Wrong turn." << endl; //FIXME:: tell which turn it is
        return;
    }
     //   */

    if(!MoveValidation(movingPiece, rank2, file2)){
        cout << "Invalid move." << endl; //FIXME: also tell which piece move was attempted
        return;
    }


    //Change values on the Piece Obj
    movingPiece->MovePiece(rank2, file2);

    // delete captured piece from Piece** vectors
    if(board[rank2][file2]->GetPointVal() != 0 && turn){ //For white's turn
        for(unsigned int i = 0; i < blackPieces.size(); i++){
            if( (*blackPieces.at(i)) == board[rank2][file2] ){
                blackPieces.erase(blackPieces.begin() + i);
            }
        }
    }
    else if(board[rank2][file2]->GetPointVal() != 0 && !turn){ //For blacks's turn
        for(unsigned int i = 0; i < whitePieces.size(); i++){
            if( (*whitePieces.at(i)) == board[rank2][file2] ){
                whitePieces.erase(whitePieces.begin() + i);
            }
        }
    }

    //move Piece* in board[][] array
    delete board[rank2][file2];
    board[rank2][file2] = movingPiece;
    board[rank1][file1] = emptySquare;

    // Pawn Promotion
    if(movingPiece->GetPointVal() == pawn || movingPiece->GetPointVal() == -pawn){
        movingPiece->PawnPromotion();
    }

    // Update piece position bit boards
    PopulateBitBoard(turn); //FIXME:: could be more efficient if it only updated the piece that moved (unless capture)
    PopulateBitBoard(!turn);


    //change turns
    turn = !turn;

    //Checks for checks
    SetCheck(turn);

    //Calls check
    if(whiteCheck){
        cout << "White is in Check!" << endl;
    } else if(blackCheck){
        cout << "Black is in Check!" << endl;
    }

    //Update possible moves for all pieces on the board
    PopulateAllMoves(true); //this needs to be after turn and setCheck

    ListColorMoves(1);
    ListColorMoves(0);

    //print board
    PrintBoard();
}

bool Board::VirtualMovePiece(Piece* movingPiece, int row, int col){
    int file1 = movingPiece->GetColumn();
    int file2 = col;
    int rank1 = movingPiece->GetRow();
    int rank2 = row;
    Piece* emptySquare = new Piece(rank1,file1,0);
    bool validity = true;
    int kingRow;
    int kingColumn;


    //Change values on the Piece Obj
    movingPiece->MovePiece(rank2, file2);

    // delete captured piece from Piece** vectors
    if(board[rank2][file2]->GetPointVal() != 0 && turn){ //For white's turn
        for(unsigned int i = 0; i < blackPieces.size(); i++){
            if( (*blackPieces.at(i)) == board[rank2][file2] ){
               blackPieces.erase(blackPieces.begin() + i);
            }
        }
    }
    else if(board[rank2][file2]->GetPointVal() != 0 && !turn){ //For blacks's turn
        for(unsigned int i = 0; i < whitePieces.size(); i++){
            if( (*whitePieces.at(i)) == board[rank2][file2] ){
                whitePieces.erase(whitePieces.begin() + i);
            }
        }
    }

    //move Piece* in board[][] array
    //delete board[rank2][file2];
    board[rank2][file2] = movingPiece;
    board[rank1][file1] = emptySquare;

    // Pawn Promotion
    if(movingPiece->GetPointVal() == pawn || movingPiece->GetPointVal() == -pawn){
        movingPiece->PawnPromotion();
    }

    // Update piece position bit boards
    PopulateBitBoard(turn); //FIXME:: could be more efficient if it only updated the piece that moved (unless capture)
    PopulateBitBoard(!turn);

    //change turns
    turn = !turn;

    //Checks for checks
   // SetCheck(turn);

    //Update possible moves for all pieces on the board
    PopulateAllMoves(false); //this needs to be after turn and setCheck
    ///Problem: moves need to be reset


    if(movingPiece->GetPointVal() > 0){
        kingRow = (*whiteKing)->GetRow(); //Get King Square
        kingColumn = (*whiteKing)->GetColumn();
        if(DetectAttack(kingRow, kingColumn, true)){
            validity = false;
        }
        else{
            validity = true;
        }
    } else{
        kingRow = (*whiteKing)->GetRow(); //Get King Square
        kingColumn = (*whiteKing)->GetColumn();
        if(DetectAttack(kingRow, kingColumn, false)){
            validity = false;
        }
        else{
            validity = true;
        }
    }

    //print board
    cout << "Game test print board  vvv" << endl;
    PrintBoard();

    return validity;
}

bool Board::MoveValidation(Piece* movingPiece, int rank2, int file2) const{
    if(movingPiece->CheckMove(rank2,file2)){
        return true;
    }
    else{
        return false;
    }
}

int Board::GetSquareFile(string squareName)const{ //Files are letters (a-h)
    int file;
    file = squareName.at(0) - 'a'; //Converts ASCII to 0-7 for board[][]
    return file;
}
int Board::GetSquareRank(string squareName)const{ //Ranks are numbers (1-8)
    int boardRank;
    boardRank = squareName.at(1) - '1';
    return boardRank;
}

/***** PRIVATE****/


string Board::GetStartSquare(string moveCommand) const{
    string startSquare;
    startSquare = moveCommand.substr(0,2);
    return startSquare;
}
string Board::GetEndSquare(string moveCommand)const{
    string endSquare;
    endSquare = moveCommand.substr(2,2);
    return endSquare;
}

