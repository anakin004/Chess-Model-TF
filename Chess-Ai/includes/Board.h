#pragma once

#include "Texture.h"
#include "util.h"
#include "VAO.h"
#include "VBO.h"
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




	Board();
	~Board();

	inline const std::array<PieceType, BOARD_SIZE>& get_board() const { return m_Board; }


private:

	std::array<PieceType, BOARD_SIZE> m_Board;

	// textures are intiialized in app startup
	Texture* m_Texture;

	VAO m_Vao;
	VBO m_Vbo;


};
