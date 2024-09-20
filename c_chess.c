#include "c_chess.h"

/*void chess_board(int white[2][8], int black[2][8]){
  printf("\n");
  printf("8\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\n\n", white[0][0], white[0][1], white[0][2], white[0][3], white[0][4], white[0][5], white[0][6], white[0][7]);
  printf("7\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\n\n", white[1][0], white[1][1], white[1][2], white[1][3], white[1][4], white[1][5], white[1][6], white[1][7]);
  printf("6\t_\t_\t_\t_\t_\t_\t_\t_\n\n");
  printf("5\t_\t_\t_\t_\t_\t_\t_\t_\n\n");
  printf("4\t_\t_\t_\t_\t_\t_\t_\t_\n\n");
  printf("3\t_\t_\t_\t_\t_\t_\t_\t_\n\n");
  printf("2\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\n\n", black[1][0], black[1][1], black[1][2], black[1][3], black[1][4], black[1][5], black[1][6], black[1][7]);
  printf("1\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\t%lc\n\n", black[0][0], black[0][1], black[0][2], black[0][3], black[0][4], black[0][5], black[0][6], black[0][7]);
  printf(" \tA\tB\tC\tD\tE\tF\tG\tH\n\n");
}*/

void draw_board_p(PIECE **board) {
    int file, rank;
    printf("    A    B    C    D    E    F    G    H \n");
    printf("  +----+----+----+----+----+----+----+----+\n");
    for (rank = 7; rank >= 0; rank--) {
        printf("%d ", rank + 1);

        for (file = 0; file < 8; file++) {
            printf("|");
            if (!board[8*rank+file]) {
                printf(" -- ");
            }             
            else {
                char piece_str[3];
                piece_str[0] = (board[8*rank+file]->side == White ? 'w' : 'b');
                switch (board[8*rank+file]->type) {
                    case Pawn:
                        piece_str[1] = 'P';
                        break;
                    case Bishop:
                        piece_str[1] = 'B';
                        break;
                    case Knight:
                        piece_str[1] = 'N';
                        break;
                    case Rook:
                        piece_str[1] = 'R';
                        break;
                    case Queen:
                        piece_str[1] = 'Q';
                        break;
                    case King:
                        piece_str[1] = 'K';
                        break;
                    default:
                        fprintf(stderr, "Error: Invalid piece type.\n");
                        exit(1);
                }
                piece_str[2] = '\0';
                printf(" %s ", piece_str);
            }
        }
        printf("| ");
        printf("%d \n", rank + 1);
        printf("  +----+----+----+----+----+----+----+----+\n");
    }
    printf("    A    B    C    D    E    F    G    H \n");
}

U64 Take_input(U64 curr_board){
	
	char str[6];
	U64 clear_b, mark_b;

	printf("\nEnter move ex.(e2-e3)\n");
	scanf("%s", str);
	clear_b = bit_XY((int)(str[0]-97), (int)(str[1]-49));
	mark_b = bit_XY((int)(str[3]-97), (int)(str[4]-49));

	if (str[0] == 'q') return 0;	
	return (curr_board & (~clear_b) | mark_b);
}
/*
int main()
{
    U64 start = 0xffff00000000ffff;
    //char move1[3];
    //char move2[3];
    //initializeBoard();
    //print_board();
    draw_board_p(Initialize_Board());
    Printbitboard(Take_input(start));
    
}
*/


/*
    // U64 H4 = 0b1000000000000000000000000000000000000000;
    // U64 E4 = 0b1000000000000000000000000000000000000;
    // U64 A4 = 0b100000000000000000000000000000000;
    // U64 E1 = 0b1000000000000000000000000000000000000000000000000000000000000;
    // U64 A2 = 281474976710656;

    // U64 knightMoves = KnightLegalMoves(H4);
    // printf("H4");
    // print_bitboard(knightMoves);

    // knightMoves = KnightLegalMoves(E4);
    // printf("E4");
    // print_bitboard(knightMoves);

    // knightMoves = KnightLegalMoves(A4);
    // printf("A4");
    // print_bitboard(knightMoves);

    // knightMoves = KnightLegalMoves(E1);
    // printf("E1");
    // print_bitboard(knightMoves);

    // knightMoves = KnightLegalMoves(A2);
    // printf("A2");
    // print_bitboard(knightMoves);

    // print_bitboard(occupancy[2]);

    // print_bitboard(occupancy[2]);
    return 0;
}*/
