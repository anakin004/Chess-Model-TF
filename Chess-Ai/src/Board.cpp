#include "Board.h"


Board::Board()
{
	
	m_WhiteBitBoard = static_cast<uint64_t>( std::pow(2, 17) - 1 );

	// we can shift the white bit board by 4 rows or 8x4 bits
	m_BlackBitBoard = m_WhiteBitBoard << ( 8*4 );



}
