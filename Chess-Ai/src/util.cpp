#include "util.h"

static constexpr int ATLAS_COLS = 6;
static constexpr int ATLAS_ROWS = 2;

AtlasUv getAtlasUV(Piece p) 
{
    int col = 0, row = 0;
    switch (p) {
        case wKing:   col = 0; row = 0; break;
        case wQueen:  col = 1; row = 0; break;
        case wRook:   col = 2; row = 0; break;
        case wBishop: col = 3; row = 0; break;
        case wKnight: col = 4; row = 0; break;
        case wPawn:   col = 5; row = 0; break;
        case bKing:   col = 0; row = 1; break;
        case bQueen:  col = 1; row = 1; break;
        case bRook:   col = 2; row = 1; break;
        case bBishop: col = 3; row = 1; break;
        case bKnight: col = 4; row = 1; break;
        case bPawn:   col = 5; row = 1; break;
        default:
            return { { 0.f,0.f }, {0.f, 0.f} };
    };
    

    float u0 = float(col) / ATLAS_COLS;
    float v0 = float(row) / ATLAS_ROWS;
    float u1 = (float(col) + 1) / ATLAS_COLS;
    float v1 = (float(row) + 1) / ATLAS_ROWS;
	return { { u0, v0 }, { u1, v1 } };
}