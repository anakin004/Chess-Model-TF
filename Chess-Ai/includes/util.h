#pragma once

#include <cstdint>
#include <glm/glm.hpp>

struct Vertex 
{
    glm::vec2 pos;
    glm::vec2 uv;
    float pickId;
};

struct AtlasUv
{
	glm::vec2 bl;
	glm::vec2 tr;
};

constexpr uint32_t BOARD_SIZE = 64;
const uint32_t SCREEN_WIDTH = 1000;
const uint32_t SCREEN_HEIGHT = 1000;

enum Piece {
    Empty = 0,

    // White pieces
    wKing,
    wQueen,
    wRook,
    wBishop,
    wKnight,
    wPawn,

    // Black pieces
    bKing,
    bQueen,
    bRook,
    bBishop,
    bKnight,
    bPawn
};

AtlasUv getAtlasUV(Piece p);
