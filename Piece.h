
#ifndef PIECE_H
#define PIECE_H
#include <string>

struct passArray{
            bool theArray[8][8];
        };

struct SquareInfo{
    std::string moveCommand;
    std::string startSquare;
    std::string endSquare;
    int file1;
    int file2;
    int rank1;
    int rank2;
};

class Piece{

    public:
        Piece(); //default constructer seems to
        Piece(int startRow, int startColumn, int pieceVal); //second constructor creates new piece


        void SetPossibleMoves(int passdRow, int col, bool setVal);
        void GeneratePossibleMoves(int startRow,int startColumn, int pieceVal);
        void EmptyPossibleMoves();

        void MovePiece(int endRow, int endColumn);//changes row, column
        void PawnPromotion();

        //Getters
        int GetRow() const;
        int GetColumn() const;
        int GetPointVal() const;
        char GetDisplayLetter() const;
        std::string GetPieceName() const;
        bool GetHasMoved() const;
        bool CheckMove(int moveRow, int moveColumn) const;

        //Print functions
        void PrintPieceInfo() const;
        void PrintPossibleMoves() const;

    private:


        int row;
        int column;
        passArray possibleMoves;
        int pointVal;
        bool hasMoved; // used for pawns, castling
};

#endif // PIECE_H
