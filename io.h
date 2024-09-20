#ifndef IO_H
#define IO_H

#include "Constants.h"

#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define get_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define pop_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))

void print_bitboard(U64 bitboard);


#endif