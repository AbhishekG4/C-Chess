#include "bitboard.h"
#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c %c %c %c %c %c %c %c\n"
#define BYTE_TO_BINARY(board)  \
  ((board) & 0x0100000000000000 ? '1' : '0'),\
  ((board) & 0x0200000000000000 ? '1' : '0'), \
  ((board) & 0x0400000000000000 ? '1' : '0'), \
  ((board) & 0x0800000000000000 ? '1' : '0'), \
  ((board) & 0x1000000000000000 ? '1' : '0'), \
  ((board) & 0x2000000000000000 ? '1' : '0'), \
  ((board) & 0x4000000000000000 ? '1' : '0'), \
  ((board) & 0x8000000000000000 ? '1' : '0')

void Printbitboard(U64 board){
	for(int i=0;i<8;i++){
		printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(board));
		board = board<<8;
	}
	printf("\n");
}

U64 XY_to_bitboard(int a, int b){
	U64 out = 1;

	return (out<<(8*(b-1) + a-1));
}
