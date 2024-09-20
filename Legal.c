#include "Legal.h"
#include <stdio.h>

void WPawnMoves(PIECE *piece, BOARD_S *board) {

	U64 moves = 0;
	U64 position = piece->Position;
	U64 c_move;
	int M[4] = {7,9,8,16};
	U64 A = 0x0101010101010101;
	U64 H = 0x8080808080808080;
	U64 R2 = 0xff00;

	for (int i=0;i<2;i++){		//Checks diagonal moves
		c_move = position<<M[i];
		if (((c_move&A)&&(position&H)) || ((c_move&H)&&(position&A)) || (!c_move)) continue;
		if(!(c_move & board->black_U)) continue;
		moves = moves | c_move;
	}

	c_move = position<<M[2];
	if (!(c_move & board->board_U)){
		moves = moves | c_move;
	}
	c_move = position<<M[3];
	if ((position & R2)&&(!(c_move & board->board_U))){
		moves = moves | c_move;
	}

	piece->L_moves = moves;
}

void BPawnMoves(PIECE *piece, BOARD_S *board) {

	U64 moves = 0;
	U64 position = piece->Position;
	U64 c_move;
	int M[4] = {7,9,8,16};
	U64 A = 0x0101010101010101;
	U64 H = 0x8080808080808080;
	U64 R7= 0x00ff000000000000;

	for (int i=0;i<2;i++){		//Checks diagonal moves
		c_move = position>>M[i];
		if (((c_move&A)&&(position&H)) || ((c_move&H)&&(position&A)) || (!c_move)) continue;
		if(!(c_move & board->white_U)) continue;
		moves = moves | c_move;
	}

	c_move = position>>M[2];
	if (!(c_move & board->board_U)){
		moves = moves | c_move;
	}
	c_move = position>>M[3];
	if ((position & R7)&&(!(c_move & board->board_U))){
		moves = moves | c_move;
	}

	piece->L_moves = moves;
}

void KnightMoves(PIECE *piece, BOARD_S *board) {//BOARD_S *board

	U64 aly_board = (piece->side) ? board->black_U : board->white_U;
	U64 position = piece->Position;
	U64 moves = 0;	//To take union of all valid moves
	U64 c_move;	//considered move
	int M[4] = {6,15,17,10};
	U64 AB = 0x0303030303030303;	//A & B file
	U64 GH = 0xc0c0c0c0c0c0c0c0;	//G & H file

	for (int i=0;i<4;i++){
		c_move = position<<M[i];
		if ((!c_move) || ((position&AB)&&(c_move&GH)) || ((position&GH)&&(c_move&AB))) continue;
		if (c_move & aly_board) continue;
		//chek for check
		moves = moves | c_move;
	}
	for (int i=0;i<4;i++){
		c_move = position>>M[i];
		if ((!c_move) || ((position&AB)&&(c_move&GH)) || ((position&GH)&&(c_move&AB))) continue;
		if (c_move & aly_board) continue;
		//check for check
		moves = moves | c_move;
	}
	
	piece->L_moves = moves;	
}


void BishopMoves(PIECE *piece, BOARD_S *board) {//BOARD_S *board

	U64 aly_board = (piece->side) ? board->black_U : board->white_U;
	U64 op_board = (piece->side) ? board->white_U : board->black_U;
	U64 position = piece->Position;
	U64 moves=0;
	U64 c_move;
	U64 c_move_p;
	int M[2] = {7,9};
	U64 A = 0x0101010101010101;
	U64 H = 0x8080808080808080;
	
	for (int i=0;i<2;i++){
		c_move = position;
		while(1){
			c_move_p = c_move;
			c_move = c_move<<M[i];
			if ((!c_move) || ((c_move&A)&&(c_move_p&H)) || ((c_move&H)&&(c_move_p&A))) break;
			if (c_move & aly_board) break;
			else if (c_move & op_board){
				moves = moves | c_move;
				break;
			}
			moves = moves | c_move;
		}
	}
	for (int i=0;i<2;i++){
		c_move = position;
		while(1){
			c_move_p = c_move;
			c_move = c_move>>M[i];
			if ((!c_move) || ((c_move&A)&&(c_move_p&H)) || ((c_move&H)&&(c_move_p&A))) break;
			if (c_move & aly_board) break;
			else if (c_move & op_board){
				moves = moves | c_move;
				break;
			}
			moves = moves | c_move;
		}
	}
	piece->L_moves = moves;
}

void RookMoves(PIECE *piece, BOARD_S *board) {//BOARD_S *board

	U64 op_board = (piece->side) ? board->white_U : board->black_U;
	U64 aly_board = (piece->side) ? board->black_U : board->white_U;
	U64 position = piece->Position;
	U64 moves=0;
	U64 c_move;
	U64 c_move_p;
	int M[2] = {1,8};
	U64 A = 0x0101010101010101;
	U64 H = 0x8080808080808080;
	
	for (int i=0;i<2;i++){
		c_move = position;
		while(1){
			c_move_p = c_move;
			c_move = c_move<<M[i];
			if ((!c_move) || ((c_move&A)&&(c_move_p&H)) || ((c_move&H)&&(c_move_p&A))) break;
			if (c_move & aly_board) break;
			else if (c_move & op_board){
				moves = moves | c_move;
				break;
			}
			moves = moves | c_move;
		}
	}
	for (int i=0;i<2;i++){
		c_move = position;
		while(1){
			c_move_p = c_move;
			c_move = c_move>>M[i];
			if ((!c_move) || ((c_move&A)&&(c_move_p&H)) || ((c_move&H)&&(c_move_p&A))) break;
			if (c_move & aly_board) break;
			else if (c_move & op_board){
				moves = moves | c_move;
				break;
			}
			moves = moves | c_move;
		}
	}
	piece->L_moves = moves;
}

void QueenMoves(PIECE *piece, BOARD_S *board) {//BOARD_S *board

	U64 op_board = (piece->side) ? board->white_U : board->black_U;
	U64 aly_board = (piece->side) ? board->black_U : board->white_U;
	U64 position = piece->Position;
	U64 moves=0;
	U64 c_move;
	U64 c_move_p;
	int M[4] = {1,7,8,9};
	U64 A = 0x0101010101010101;
	U64 H = 0x8080808080808080;
	
	for (int i=0;i<4;i++){
		c_move = position;
		while(1){
			c_move_p = c_move;
			c_move = c_move<<M[i];
			if ((!c_move) || ((c_move&A)&&(c_move_p&H)) || ((c_move&H)&&(c_move_p&A))) break; //Move within board?
			if (c_move & aly_board) break;
			else if (c_move & op_board){
				moves = moves | c_move;
				break;
			}
			moves = moves | c_move;
		}
	}
	for (int i=0;i<4;i++){
		c_move = position;
		while(1){
			c_move_p = c_move;
			c_move = c_move>>M[i];
			if ((!c_move) || ((c_move&A)&&(c_move_p&H)) || ((c_move&H)&&(c_move_p&A))) break;
			if (c_move & aly_board) break;
			else if (c_move & op_board){
				moves = moves | c_move;
				break;
			}
			moves = moves | c_move;
		}
	}
	piece->L_moves = moves;
}

void KingMoves(PIECE *piece, BOARD_S *board) {

	U64 position = piece->Position;
	U64 aly_board = (piece->side) ? board->black_U : board->white_U;
	U64 moves=0;
	U64 c_move;
	int M[4] = {1,9,8,7};
	U64 castling = board->Castling;
	U64 castle_s ,castle_l, c_region;
	U64 A = 0x0101010101010101;
	U64 H = 0x8080808080808080;

	for (int i=0;i<4;i++){
		c_move = position<<M[i];
		if ((!c_move) || ((c_move&A)&&(position&H)) || ((c_move&H)&&(position&A))) continue;
		if (c_move & aly_board) continue;
		moves = moves | c_move;
	}
	for (int i=0;i<4;i++){
		c_move = position>>M[i];
		if ((!c_move) || ((c_move&A)&&(position&H)) || ((c_move&H)&&(position&A))) continue;
		if (c_move & aly_board) continue;
		moves = moves | c_move;
	}

	if (castling){
		if (piece->side){
			castle_s = castling & 0xf000000000000000;
			castle_l = castling & 0xf00000000000000;
			if (castle_s){
				c_region = castle_s | castle_s>>1;
				if (!(c_region & board->board_U)&&!(c_region & board->white_moves_U)){
					moves = moves | castle_s;
				}
			}
			if (castle_l){
				c_region = castle_l | castle_l<<1 | castle_l>>1;
				if (!(c_region & board->board_U)&&!(c_region & board->white_moves_U)){
					moves = moves | castle_l;
				}
			}
		}
		else{
			castle_s = castling & 0x0f;
			castle_l = castling & 0xf;
			if (castle_s){
				c_region = castle_s | castle_s>>1;
				if (!(c_region & board->board_U)&&!(c_region & board->black_moves_U)){
					moves = moves | castle_s;
				}
			}
			if (castle_l){
				c_region = castle_l | castle_l<<1 | castle_l>>1;
//printf("c_region & board\n");//-------------------------
//Printbitboard(c_region);//---------------------------
				if (!(c_region & board->board_U)&&!(c_region & board->black_moves_U)){
					moves = moves | castle_l;
				}
			}
		}
	}

	piece->L_moves = moves;
}
