#ifndef BOARD_H
#define BOARD_H
#include <math.h>
#include "Constants.h"

typedef struct Board_status BOARD_S;
struct Board_status{
	U64	white_U;	//Union of all white piece positions
	U64	black_U;
	U64	board_U;
	U64	white_moves_U;
	U64	black_moves_U;
	U64	King_positions;
	U64	Castling;
	int	Check;		//-1 if black uunder check, 1 if white under check & 0 if no check
	int	Checkmate;	//Simillar to above scheme
};

int Get_X(U64 bitboard);
int Get_Y(U64 bitboard);
int Get_I(U64 bitboard);
U64 bit_XY(int x, int y);
#endif
