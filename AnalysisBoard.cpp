#include "AnalysisBoard.h"

AnalysisBoard::AnalysisBoard()
{
    //ctor
}


/*
bool AnalysisBoard::KingDanger(Piece* piece, int row, int col){ //tests a move to make sure the king is unable to be captured
    Piece* movingPiece = piece;
    int rank1 = piece->GetRow();
    int file1 = piece->GetColumn();

    int rank2 = row;
    int file2 = col;
    Piece* emptySquare = new Piece(piece->GetRow(), piece->GetColumn(), 0);

    //Change values on the Piece Obj
    movingPiece->MovePiece(rank2, file2);

    // delete captured piece from Piece** vectors

    if(board[rank2][file2]->GetPointVal() != 0 && turn){ //For white's turn
        for(int i = 0; i < blackPieces.size(); i++){
            if( (*blackPieces.at(i)) == board[rank2][file2] ){
                blackPieces.erase(blackPieces.begin() + i);
            }
        }
    }
    else if(board[rank2][file2]->GetPointVal() != 0 && !turn){ //For blacks's turn
        for(int i = 0; i < whitePieces.size(); i++){
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
    //turn = !turn;

    //Checks for checks
    //SetCheck(turn);

    //Update possible moves for all pieces on the board
    PopulateAllMoves(0); //this needs to be after turn and setCheck
    PopulateAllMoves(0); //FIXME:: efficiency --- King's moves depend on oppenent's possible moves, meaning enemy's moves must be generated first(or just do the whole thing twice)
    /*** Problem:: unchecked recursion in using the Populate moves to populate moves**/


    //ListColorMoves(1);
    //ListColorMoves(0);

    //SetCheck(turn);

 /*   return GetCheck(turn);//GetCheck(turn);
}/**/
