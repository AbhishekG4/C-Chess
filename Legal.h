#ifndef LEGAL_H
#define LEGAL_H

#include "Piece.h"
#include "Board.h"
#include "Constants.h"
#include "io.h"
#include "bitboard.h"


void WPawnMoves (PIECE *piece, BOARD_S *board);
void BPawnMoves (PIECE *piece, BOARD_S *board);
void KnightMoves(PIECE *piece, BOARD_S *board);//BOARD_S *board
void BishopMoves(PIECE *piece, BOARD_S *board);//BOARD_S *board
void RookMoves  (PIECE *piece, BOARD_S *board);//BOARD_S *board
void QueenMoves (PIECE *piece, BOARD_S *board);//BOARD_S *board
void KingMoves  (PIECE *piece, BOARD_S *board);

#endif
