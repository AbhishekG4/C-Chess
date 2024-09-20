#include "Board.h"

int Get_X(U64 bitboard){
	
	int x;

	x = ((int)(log(bitboard)/log(2))%8);
	return x;
}

int Get_Y(U64 bitboard){

	int y;

	y = (int)((log(bitboard)/log(2))/8);
	return y;
}

int Get_I(U64 bitboard){
	
	return (log(bitboard)/log(2));
}

U64 bit_XY(int x, int y){
	U64 bboard = 1;

	return bboard<<(y*8+x);
}
