#include "tree_stats.h"

void Print_children(SIM_NODE *parent){
	SIM_NODE *node = parent->Child;
	int sum =0;

	if (!node){
		printf("No children\n");
		return;
	}
	printf("Children are:-\n");
	while(node){
		sum++;
		Printbitboard(node->Status.board_U);
		node = node->Next;
	}
	printf("total children = %d\n", sum);
	return;
}

void Record_node(int name,SIM_NODE * node){
	
	FILE *fp;
	switch(name){
	case 1:
		fp = fopen("fail_node.txt","w");
		break;
	case 2:
		fp = fopen("fail_nodep.txt","w");
		break;
	case 3:
		fp = fopen("fail_nodepp.txt","w");
		break;
	}
	fprintf(fp, "\n====================\n");
	fprintf(fp, "white_U: %llu\n", node->Status.white_U);
	fprintf(fp, "black_U: %llu\n", node->Status.black_U);
	fprintf(fp, "board_U: %llu\n", node->Status.board_U);
	fprintf(fp, "white_moves_U: %llu\n", node->Status.white_moves_U);
	fprintf(fp, "black_moves_U: %llu\n", node->Status.black_moves_U);
	fprintf(fp, "King_positions: %llu\n", node->Status.King_positions);
	fprintf(fp, "Castling: %llu\n", node->Status.Castling);
	fprintf(fp, "Check: %d\n", node->Status.Check);
	fprintf(fp, "Checkmate: %d\n",node->Status.Checkmate);
	fclose(fp);
}
