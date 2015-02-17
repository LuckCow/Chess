
#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "Piece.h"

class Board{
    public:
        Board();
        void ResetBoard();
        void ResetTestBoard();
        void PrintBoard() const;
        void PrintBoardState() const;

        bool GetTurn() const;
        Piece* GetPiece(int row/*[rank]*/, int column/*[file]*/) const;
        int GetPieceVal(int row, int column) const;

        void PopulateBitBoard(bool color);
        void PrintBitBoard(bool color)const;
        bool GetBitBoard(int row, int column, bool color) const;

        void SetCheck(bool color);
        bool GetCheck(bool color) const;
        bool DetectAttack(int sqRow, int sqCol, bool color);
        void PopulatePieceVector(bool color);
        void PrintPieceVector(bool color) const;

        void PopulateAllMoves();
        void PopulatePossibleMoves(Piece* piece);
        void GenerateCheckMoves();
        void GenerateRookMoves(Piece* piece);
        void GenerateBishopMoves(Piece* piecePtr);
        void GenerateKnightMoves(Piece* piecePtr);
        void GenerateKingMoves(Piece* piecePtr);
        void GeneratePawnMoves(Piece* piecePtr);


        void MovePiece(std::string moveCommand);

        bool MoveValidation(Piece* movingPiece, int rank2, int file2) const;

        int GetSquareFile(std::string squareName) const;
        int GetSquareRank(std::string squareName) const;


    private:
        bool turn; //true = white, false = black
        Piece* board[8][8];
        bool whiteBitBoard[8][8];
        bool blackBitBoard[8][8];

        //these pointers point to the king pointer. they are used to find the king, even after he has moved
        Piece** whiteKing;
        Piece** blackKing;

        std::vector<Piece**> whitePieces;
        std::vector<Piece**> blackPieces;

        bool whiteCheck;
        bool blackCheck;


        std::string GetStartSquare(std::string moveCommand) const;
        std::string GetEndSquare(std::string moveCommand)const;


};

#endif // BOARD_H
