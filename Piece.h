#ifndef PIECE_H
#define PIECE_H

#include <stdbool.h>
#include "Board.h"
#include "Constants.h"

enum PType {King, Queen, Rook, Bishop, Knight, Pawn};
enum Side {White, Black};

typedef struct t_Piece PIECE;

typedef U64 (*MU)(PIECE *piece, BOARD_S *board);   //function pointer to function for legal move generation MU -> Move updade

struct t_Piece{
	enum PType type;
	enum Side side;
	int	Value;
	U64	L_moves;
	U64	Position;
	MU	Moves_func;
};

/*PIECE *Create_Piece(enum PType Type, enum Side Side, U64 position);
PIECE **Initialize_Board(void);
PIECE *Copy_Piece(PIECE *piece);
void Delete_Piece(PIECE *Piece);
PIECE **Copy_Board(PIECE **board);
void Delete_Board(PIECE **board);
*/

#endif
