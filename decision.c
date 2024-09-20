#include <stdio.h>
#include "decision.h"
#include "Board.h"
#include "Piece.h"
#include "tree.h"


//Input depth = 0 to main function
double minimax(SIM_NODE *Node, int depth, double alpha, double beta, SIM_NODE **m_node) {
        // to be implemented
	double Score, maxScore, minScore;
	SIM_NODE *Child, *temp;
//printf("%X %X %X\n", Node,Node->Child,depth);//-----------------------------------
        if (!depth || !Node->Child) {
        	return	evaluate_board(Node);
    	}

    	if (!Node->color) {
		maxScore = -999999999;
		
		Child = Node->Child;
		while(Child){
			Score = minimax(Child, depth-1, alpha, beta, &temp);
			if (Score>=maxScore){
				maxScore = Score;
				*m_node = Child;
			}
			alpha = (alpha >= Score) ? alpha : Score;
			if (alpha>=beta){
				 break;
			}
			Child = Child->Next;
		}
		Node->score = maxScore;	
		return maxScore;
	}

    	else {
		minScore = 999999999;
		
		Child = Node->Child;
		while(Child){
			Score = minimax(Child, depth-1, alpha, beta, &temp);
			if (Score<=minScore){
				minScore = Score;
				*m_node = Child;
			}
			beta = (beta <= Score) ? beta : Score;
			if (alpha>=beta){
				 break;
			}
			Child = Child->Next;
		}
		Node->score = minScore;
		return minScore;
	}
}


double evaluate_board(SIM_NODE *node){
	double sum=0;

	if (node->Status.Checkmate > 0){
		return node->score;
	}

	for (int i=0;i<64;i++){
		if (!node->Board[i]) continue;
		sum =sum + node->Board[i]->Value;
	}
	return sum;
}
