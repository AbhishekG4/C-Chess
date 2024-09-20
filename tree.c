#include "tree.h"
#include "c_chess.h"//------------
#include "bitboard.h"//---------------
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


SIM_NODE *Create_Node(SIM_NODE *parent, PIECE **board, enum Side n_col){
	

	SIM_NODE *node = malloc(sizeof(SIM_NODE));
	if (!node){
		printf("Malloc unsuccessful at Create_node\n");
	}

	node -> Status.white_U =0;
	node -> Status.black_U =0;
	node -> Status.board_U =0;
	node -> Status.white_moves_U =0;
	node -> Status.black_moves_U =0;
	node -> Status.King_positions =0;
	node -> Status.Check =0;
	node -> Status.Checkmate =0;

	node -> Parent = parent;
	node -> Board = board;
	node -> color = n_col;
	node -> Next = node -> Prev = node -> Child = NULL;

	return node;
}

void Delete_Node(SIM_NODE *node){
	
	Delete_Board(node->Board);
	free(node);
}

void Create_Childlist(SIM_NODE *parent, enum Side p_col){
	
	//Get all legal moves for board present in parent
	//Iterate through moves. For each move ...
		//Create board
		//Create node
		//{{call func for node. func returns null if depth = full depth}}
		//attatch parent to first node and save pointer
		//do same in next iteration and attatch to previous node
}

void Delete_Childlist(SIM_NODE *parent){
	SIM_NODE *node = parent->Child;
	if (!parent->Child) return;		//Base case
	while(node->Next){			//Deletes all but last in childlist
		Delete_Childlist(node);
		node = node->Next;
		Delete_Node(node->Prev);
	}
	Delete_Childlist(node);			//Deletes last node in childlist
	Delete_Node(node);
	parent->Child = NULL;
}

TREE *Create_Tree(PIECE **board, enum Side col, int depth){

	TREE *tree = malloc(sizeof(TREE));
	if (!tree){
		printf("Malloc unsuccessful at Create_Tree\n");
	}
	
	tree -> Origin = Create_Node(NULL, board, col);
	tree -> Depth = depth;

	return tree;
}

void Delete_Tree(TREE *tree){
	Delete_Childlist(tree->Origin);
	Delete_Node(tree->Origin);
	free(tree);
}

SIM_NODE *Reg_Move(SIM_NODE *parent, U64 s_position, U64 e_position, U64 castling){		//Reg move for regular move

	SIM_NODE *new_n;
	PIECE **n_board;
	U64	W_moves=0, B_moves=0;
	U64	w_check=0, b_check=0;	//white UNDER check/ black under check

	n_board = Copy_Board(parent->Board);		//created(copied) new board
	if (n_board[Get_I(e_position)]){		//If capture, deletes captured piece
		Delete_Piece(n_board[Get_I(e_position)]);
	}
	n_board[Get_I(e_position)] = n_board[Get_I(s_position)];	//makes move on new board
	n_board[Get_I(s_position)] = NULL;
	n_board[Get_I(e_position)]->Position = e_position;		//updates position bitboard

	new_n = Create_Node(parent, n_board, !(parent->color));
	
	//Updating board status (black, white, board Us and castling)
	if (parent->color){								//Black's move
		new_n->Status.black_U = (parent->Status.black_U & ~s_position);
		new_n->Status.black_U = (new_n->Status.black_U | e_position);
		new_n->Status.white_U = (parent->Status.white_U & ~e_position);	//Clears end pos
	}
	else{										//White's move
		new_n->Status.white_U = (parent->Status.white_U & ~s_position);	//Clears start pos
		new_n->Status.black_U = (parent->Status.black_U & ~e_position);	//Clears end pos
		new_n->Status.white_U = (new_n->Status.white_U | e_position);	//Mark end pos
	}
	new_n->Status.board_U = new_n->Status.black_U |	new_n->Status.white_U;
	new_n->Status.Castling = castling;
	
	new_n->Status.King_positions = parent->Status.King_positions;
	if (new_n->Status.King_positions & s_position){		//updates king positions if king is moved.
		new_n->Status.King_positions = (new_n->Status.King_positions & ~s_position) | e_position;
	}
	
	//Updating L moves and remaining board status
	for (int i=0; i<64; i++){
		if(!n_board[i]) continue;
		n_board[i]->Moves_func(n_board[i], (BOARD_S *)&new_n->Status);	//Updates L moves
		if (n_board[i]->side){
			B_moves = B_moves | n_board[i]->L_moves;
		}
		else{
//printf("type= %d\n", n_board[i]->type);
//Printbitboard(n_board[i]->L_moves);
			W_moves = W_moves | n_board[i]->L_moves;
		}
	}
	new_n->Status.white_moves_U = W_moves;
	new_n->Status.black_moves_U = B_moves;		//Updates union of all legal moves

	if (new_n->Status.King_positions & (W_moves | B_moves)){		//Checks for check
		new_n->Status.Check = 1;
		w_check = B_moves & new_n->Status.King_positions;
		b_check = W_moves & new_n->Status.King_positions;
	}
	if ((w_check && !parent->color) || (b_check&&parent->color) || (parent->Status.Check&&new_n->Status.Check)){//delete
		Delete_Node(new_n);
		return NULL;
	}

	return new_n;	
}

TREE *Init_start_Tree(void){

	PIECE **s_board = Initialize_Board();
	TREE *tree = Create_Tree(s_board, White, 0);
	U64	R12 = 0XFFFF;
	U64	R78 = 0XFFFF000000000000;
	U64	W_moves = 0, B_moves=0;

	tree->Origin->Status.white_U = R12;
	tree->Origin->Status.black_U = R78;
	tree->Origin->Status.board_U = R12 | R78;
	tree->Origin->Status.King_positions = 0X1000000000000010;
	tree->Origin->Status.Castling = 0x4400000000000044;

	//Updating L moves and remaining board status
	for (int i=0; i<64; i++){
		if(!s_board[i]) continue;
		s_board[i]->Moves_func(s_board[i], (BOARD_S *)&tree->Origin->Status);	//Updates L moves
		if (s_board[i]->side){
			B_moves = B_moves | s_board[i]->L_moves;
		}
		else{
			W_moves = W_moves | s_board[i]->L_moves;
		}
	}
	tree->Origin->Status.white_moves_U = W_moves;
	tree->Origin->Status.black_moves_U = B_moves;		//Updates union of all legal moves
	
	
	return tree;
}

void Add_Layers_Node (SIM_NODE *parent, int n){	//Where n is number of layers to add
assert(!parent->Child);
	
	if (n==0)	return;			//Base case

	int Iter[64] = {27,35,36,28,20,19,18,26,34,42,43,44,45,37,29,21,13,12,11,10,9,17,25,33,41,49,50,51,52,53,54,46,38,30,22,14,6,5,4,3,2,1,0,8,16,24,32,40,48,56,57,58,59,60,61,62,63,55,47,39,31,23,15,7};
	PIECE **board = parent->Board;
	int j, flag=1;
	U64 bmask, L_moves, move;
	SIM_NODE *node, *prev=NULL;

	for (int i=0;i<64;i++){				//Iterates through squares of board
		bmask = 1;
		j = Iter[i];

		if (!board[j] || board[j]->side != parent->color) continue;	//Filters out opposite and NULL squares
		
		L_moves = board[j]->L_moves;
		for(int p=0;p<64;p++){
			bmask = (unsigned long long)1<<p;
			move = L_moves & bmask;
			if (!move) continue;
			node = Sim_Move(parent, board[j]->Position, move);
			if (!node) continue;
			if (flag){
				parent->Child = node;
				flag =0;
			}
			if (prev){
				prev->Next = node;
				node->Prev = prev;
			}
			prev = node;
		}
	}
	
	node = parent->Child;
	if (!node){				//if no children
		if (parent->Status.Check){
			parent->score = (parent->color) ? 2000000000 : -2000000000;
			parent->Status.Checkmate = 1;
		}
		else{
			parent->score = 0; //stalemate
			parent->Status.Checkmate = -1;

printf("stale found\n");//----------------
		}
		
		return;
	}
	while (node->Next){
		Add_Layers_Node(node, n-1);
		node = node->Next;
	}
	Add_Layers_Node(node, n-1);
}

int Shift_Tree(TREE *tree, U64 move_board_U){
	
	SIM_NODE *node = tree->Origin->Child;
	SIM_NODE *n_origin=NULL;

	while (node->Next){
		node = node->Next;
		if (node->Prev->Status.board_U == move_board_U){
			n_origin = node->Prev;
			continue;
		}
		Delete_Childlist(node->Prev);
		Delete_Node(node->Prev);
	}
	if (node->Status.board_U == move_board_U){
		n_origin = node;
	}
	else{
		Delete_Childlist(node);
		Delete_Node(node);
	}
	if (!n_origin){
		printf("Shift_Tree couldn't find move\n");
		return 1;
	}

	n_origin->Prev = n_origin->Next = n_origin->Parent = NULL;
	Delete_Node(tree->Origin);
	tree->Origin = n_origin;
	Add_Layers_Tree(tree->Origin, 1);
	return 0;
}

void Add_Layers_Tree (SIM_NODE *parent, int n){
	
	SIM_NODE *node = parent;

	if (node->Child){
		node = node->Child;
		while(node->Next){
			Add_Layers_Tree(node, n);
			node = node->Next;
		}
		Add_Layers_Tree(node, n); //Operates on last node in list as it was excluded by the loop
		
	}
	else{				//Base case
		Add_Layers_Node(node, n);
	}
}


SIM_NODE *Sim_Move(SIM_NODE *parent, U64 s_position, U64 e_position){
	
	SIM_NODE *node, *t_node;
	int i;
	U64 castling = parent->Status.Castling;
	U64 R_pos[13] = {0x80, 0x40,  0x20, 0x1, 0x4,  0x8, 0x100000000000000, 0x400000000000000, 0x800000000000000, 0x8000000000000000, 0x4000000000000000, 0x2000000000000000, 0};	//rook_s,king_e,rook_e

	switch (parent->Board[Get_I(s_position)]->type){
		case King:
			if (parent->color){		//updates castling flag and checks whether move is a cstle or not
				castling = castling & ~(0xff00000000000000);
				if (!(e_position & parent->Status.Castling)) break;		//if move is not a castle break out of big switch
			}
			else{
				castling = castling & ~(0xff);
				if (!(e_position & parent->Status.Castling)) break;

			}		
			switch (e_position){		//assigns index of rook to be moved
				case 0x40: i=0; break;
				case 0x4: i=3; break;
				case (unsigned long long)0x400000000000000: i=6; break;
				case (unsigned long long)0x4000000000000000: i=9; break;
			}
Record_node(3,parent->Parent->Parent);//---------------
Record_node(2,parent->Parent);//---------------
Record_node(1,parent);//---------------
			t_node = Reg_Move(parent, s_position, e_position, castling);	//moves King
			node = Reg_Move(t_node, R_pos[i], R_pos[i+2], castling);	//moves rook
printf("=1=\n");//-------------------
draw_board_p(parent->Board);//----------------
			Delete_Node(t_node);
			node->Parent = parent;
			return node;
			 
		case Rook:
			switch (s_position){		//gets king castling position for rook moved
				case 0x80: i=1; break;
				case 0x1: i=4; break;
				case (unsigned long long)0x100000000000000: i=7; break;
				case (unsigned long long)0x8000000000000000: i=10;break;
				default: i=12;
			}
			castling = castling & ~R_pos[i];
			break;


		case Pawn:
			if (!(e_position & 0xff00000000000000)) break;
			Delete_Piece(parent->Board[Get_I(s_position)]);			//puts a queen in place of pawn
			parent->Board[Get_I(s_position)] = Create_Piece(Queen, parent->color, s_position);
			break;
	}

	node = Reg_Move(parent, s_position, e_position, castling);
	return node;
}


