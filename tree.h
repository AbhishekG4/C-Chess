#ifndef TREE_H
#define TREE_H
#include "Board.h"
#include "Piece.h"
#include "Moves.h"
#include <stdlib.h>

typedef struct Sim_Node SIM_NODE;
typedef struct t_tree TREE;

struct Sim_Node{
	BOARD_S Status;
	PIECE **Board;
	double score;
	SIM_NODE *Parent;
	SIM_NODE *Next;
	SIM_NODE *Prev;
	SIM_NODE *Child;
	enum Side color;
};

struct t_tree{
	SIM_NODE *Origin;
	int	 Depth;
};

SIM_NODE *Create_Node(SIM_NODE *parent, PIECE **board, enum Side n_col);	//n_col = node color

void Delete_Node(SIM_NODE *node);

void Create_Childlist(SIM_NODE *parent, enum Side p_col);	//p_col = parent color

void Delete_Childlist(SIM_NODE *parent);

TREE *Create_Tree(PIECE **board, enum Side col, int depth);

void Delete_Tree(TREE *tree);

SIM_NODE *Sim_Move(SIM_NODE *parent, U64 s_position, U64 e_position);	//returns NULL if invalid king related move

SIM_NODE *Reg_Move(SIM_NODE *parent, U64 s_position, U64 e_position, U64 castling);

TREE *Init_start_Tree(void);

int Shift_Tree(TREE *tree, U64 move_board_U);

void Add_Layers_Node(SIM_NODE *parent, int n);

void Add_Layers_Tree(SIM_NODE *parent, int n);
#endif
