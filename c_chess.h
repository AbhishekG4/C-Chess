#ifndef C_CHESS_H
#define C_CHESS_H
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#include "Constants.h"
#include "Legal.h"
#include "Board.h"
#include "Piece.h"
#include "bitboard.h"

void draw_board_p(PIECE **board);
U64 Take_input(U64 curr_board);
#endif
