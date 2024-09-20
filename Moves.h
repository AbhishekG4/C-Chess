#ifndef MOVES_H
#define MOVES_H
#include <stdio.h>
#include <stdlib.h>
#include "Piece.h"
#include "Legal.h"


PIECE *Create_Piece(enum PType Type, enum Side Side, U64 position);
PIECE **Initialize_Board(void);
PIECE *Copy_Piece(PIECE *piece);
void Delete_Piece(PIECE *Piece);
PIECE **Copy_Board(PIECE **board);
void Delete_Board(PIECE **board);
void Print_Board(PIECE **board);

#endif
