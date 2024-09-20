#include "Board.h"
#include "Piece.h"
#include "Moves.h"
#include "Legal.h"
#include "c_chess.h"
#include "tree.h"
#include "decision.h"
#include "tree_stats.h"
#include "bitboard.h"

int main(void){
	TREE *tree;
	SIM_NODE *ai_move;
	U64	move;
	double s;
	int turn, dep=3, ai_turn = 1;	//1 for moves first
	
	tree = Init_start_Tree();
	Add_Layers_Node(tree->Origin, dep);
	tree->Depth = dep;
	printf("Built tree\n");
	s = minimax(tree->Origin, tree->Depth, -20000000, 20000000, &ai_move);
	draw_board_p(tree->Origin->Board);
	
	
	while(1){
		turn = !tree->Origin->color;
		if (ai_turn && turn){
			printf("%s's turn\n", (turn) ? "White":"Black");
printf("AI choice:\n");//-----------------
Printbitboard(ai_move->Status.board_U);//------------
//Print_children(tree->Origin); //-------------
printf("shifting tree...\n");//----------------------
			Shift_Tree(tree, ai_move->Status.board_U);
printf("tree shifted\n");//-----------------
		}
		else{
			printf("%s's turn\n", (turn) ? "White":"Black");
			move = Take_input(tree->Origin->Status.board_U);
			if (!move) break;
Print_children(tree->Origin); //-------------
printf("King moves\n");//-----------------
Printbitboard(tree->Origin->Board[60]->L_moves);//------------
printf("shifting tree...\n");//----------------------
			Shift_Tree(tree, move);
printf("tree shifted\n");//-----------------
		}
printf("performing minimax...\n");//---------------
		s = minimax(tree->Origin, tree->Depth, -20000000, 20000000, &ai_move);
printf("minimax finished\n");//---------------
		draw_board_p(tree->Origin->Board);
		if (tree->Origin->Status.Checkmate){
			printf("\n mate! %s wins!!\n", (tree->Origin->color) ? "Black":"White");
			break;
		}
	}
	Delete_Tree(tree);
}

	



