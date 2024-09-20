#include "Moves.h"

PIECE *Create_Piece(enum PType Type, enum Side Side, U64 position){
	
	PIECE *piece = malloc(sizeof(PIECE));
	if (!piece){
		printf("malloc failed at Create_Piece\n");
	}
	
	piece->type = Type;
	piece->side = Side;
	switch(Type){
		case King:
			piece->Value = (Side) ? -1000:1000;
			piece->Moves_func = &KingMoves;
			break;
		case Queen:
			piece->Value = (Side) ? -30:30;
			piece->Moves_func = &QueenMoves;
			break;
		case Rook:
			piece->Value = (Side) ? -15:15;
			piece->Moves_func = &RookMoves;
			break;
		case Bishop:
			piece->Value = (Side) ? -10:10;
			piece->Moves_func = &BishopMoves;
			break;
		case Knight:
			piece->Value = (Side) ? -9:9;
			piece->Moves_func = &KnightMoves;
			break;
		case Pawn:
			piece->Value = (Side) ? -2:2;
			piece->Moves_func = (Side) ? &BPawnMoves : &WPawnMoves;
			break;
	}
	piece->Position = position;
	piece->L_moves = 0;

	return piece;
}


PIECE **Initialize_Board(void){
	
	PIECE **board = malloc(sizeof(PIECE *)*64);
	if (!board){
		printf("malloc failed at Initialize_Board\n");
	}

	U64	pos = 1;

	board[Get_I(pos)] = Create_Piece(Rook, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Knight, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Bishop, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Queen, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(King, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Bishop, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Knight, White, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Rook, White, pos);	//pos=8

	for(int i=0;i<8;i++){
		pos=pos<<1;
		board[Get_I(pos)] = Create_Piece(Pawn, White, pos);	//pos=16
	}

	for (int i=0;i<32;i++){
		pos = pos<<1;
		board[Get_I(pos)] = NULL;
	}

	for (int i=0;i<8;i++){
		pos=pos<<1;
		board[Get_I(pos)] = Create_Piece(Pawn, Black, pos);	//pos=56
}

	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Rook, Black, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Knight, Black, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Bishop, Black, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Queen, Black,  pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(King, Black, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Bishop, Black, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Knight, Black, pos);
	pos = pos<<1;
	board[Get_I(pos)] = Create_Piece(Rook, Black, pos);	//pos=8

	return board;
}	

void Print_Board(PIECE **board){
	int p=0, e=0;
	
	for (int i=0;i<64;i++){
		if (board[i]) p++;//printf("1");
		if (board[i] == NULL) e++;//printf("0");
	}
}

PIECE *Copy_Piece(PIECE *piece){
	
	PIECE *n_piece = malloc(sizeof(PIECE));
	if(!n_piece){
		printf("Failed malloc at Copy_Piece\n");
	}
	
	n_piece->type = piece->type;
	n_piece->side = piece->side;
	n_piece->Value= piece->Value;
	n_piece->L_moves = piece->L_moves;
	n_piece->Position = piece->Position;
	n_piece->Moves_func = piece->Moves_func;

	return n_piece;
}

void Delete_Piece(PIECE *piece){
	
	free(piece);
}

PIECE **Copy_Board(PIECE **board){

	PIECE **n_board = malloc(sizeof(PIECE *)*64);
	if (!n_board){
		printf("malloc failed at copy board\n");
	}

	for (int i=0; i<64; i++){
		if (board[i]){
			n_board[i] = Copy_Piece(board[i]);
		}
		else{
			n_board[i] = NULL;
		}
	}
	
	return n_board;
}

void Delete_Board(PIECE **board){
	
	for (int i=0; i<64; i++){
		if (board[i]){
			Delete_Piece(board[i]);
			board[i] = NULL;
		}
	}
	free(board);
}
