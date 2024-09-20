#ifndef DECISION_H
#define DECISION_H
#include "tree.h"
#include "Piece.h"

double minimax(SIM_NODE *Node, int depth, double alpha, double beta, SIM_NODE **m_node);
double evaluate_board(SIM_NODE *node);


#endif 
