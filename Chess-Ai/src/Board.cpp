#include "Board.h"
#include "util.h"

Board::Board()
    : m_Texture(&Texture::get_texture(0)),
      m_Vao(),
      m_Vbo()
{

    m_Board = {
        // 8th row (black pieces)
        bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook,

        // 7th row (black pawns)
        bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn,

        // 6th to 3rd row (empty squares)
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,


        // 2nd row (white pawns)
        wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn,

        // 1st row (white pieces)
        wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook
    };
}
