#pragma once

#include "util.h"
#include <array>

class Board
{

public:

	enum PieceType : uint8_t
	{
		Empty,

		wPawn,
		wKnight,
		wBishop,
		wRook,
		wQueen,
		wKing,

		bPawn,
		bKnight,
		bBishop,
		bRook,
		bQueen,
		bKing
	};


	// bitboard starts at top left and goes row by row
	enum class BitBoardPosition : uint8_t
	{
		a8, b8, c8, d8, e8, f8, g8, h8,
		a7, b7, c7, d7, e7, f7, g7, h7,
		a6, b6, c6, d6, e6, f6, g6, h6,
		a5, b5, c5, d5, e5, f5, g5, h5,
		a4, b4, c4, d4, e4, f4, g4, h4,
		a3, b3, c3, d3, e3, f3, g3, h3,
		a2, b2, c2, d2, e2, f2, g2, h2,
		a1, b1, c1, d1, e1, f1, g1, h1
	};


	Board();
	~Board() = default;


	inline uint64_t& get_white_bitboard() { return m_WhiteBitBoard; }
	inline uint64_t& get_black_bitboard() { return m_BlackBitBoard; }
	inline uint64_t& get_king_bitboard() { return m_KingBitBoard; }
	inline std::array<PieceType, BOARD_SIZE>& get_normal_board() { return m_Board; }


private:

	uint64_t m_WhiteBitBoard;
	uint64_t m_BlackBitBoard;
	uint64_t m_KingBitBoard;
	std::array<PieceType, BOARD_SIZE> m_Board;


};
