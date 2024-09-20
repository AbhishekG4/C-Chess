OBJS = c_chess.o io.o Legal.o Board.o
CC =  gcc
FLAGS = -c -g -Wall -std=c11
LFLAGS = -g -Wall -std=c11 -lm

all: c_chess

Piece.o: Piece.h Piece.c
	$(CC) $(FLAGS) Piece.c -o Piece.o

c_chess: c_chess.o Legal.o Board.o Moves.o bitboard.o
	$(CC) $(LFLAGS) c_chess.o Moves.o Legal.o bitboard.o Board.o -o c_chess

c_chess.o: c_chess.c Constants.h 
	$(CC) $(FLAGS) c_chess.c -o c_chess.o

io.o: io.c io.h Constants.h
	$(CC) $(FLAGS) io.c -o io.o

decision.o: decision.c decision.h
	$(CC) $(FLAGS) decision.c -o decision.o

Legal.o: Legal.c Legal.h Constants.h
	$(CC) $(FLAGS) Legal.c -o Legal.o

Moves.o: Moves.h Piece.h Moves.c
	$(CC) $(FLAGS) Moves.c -o Moves.o

Board.o: Board.c Board.h Constants.h
	$(CC) -c $(LFLAGS) Board.c -o Board.o

bitboard.o: bitboard.c bitboard.h Constants.h
	$(CC) $(FLAGS) bitboard.c -o bitboard.o

tree_stats.o: tree_stats.c tree_stats.h Constants.h
	$(CC) $(FLAGS) tree_stats.c -o tree_stats.o

tree.o: tree.h tree.c
	$(CC) $(FLAGS) tree.c -o tree.o

main2.o: main2.c tree.h
	$(CC) $(FLAGS) main2.c -o main2.o
main2: main2.o tree.o Moves.o Board.o Legal.o
	gcc -Wall -std=c11 Board.o Legal.o Moves.o tree.o main2.o -lm -o main2

main3.o: main3.c Piece.h tree.h Moves.h
	$(CC) $(FLAGS) main3.c -o main3.o
main3: main3.o Legal.o Moves.o Board.o bitboard.o tree.o decision.o c_chess.o tree_stats.o
	gcc -g -Wall -std=c11 Legal.o bitboard.o tree_stats.o Board.o tree.o Moves.o decision.o c_chess.o main3.o -lm -o main3

main.o: main.c Piece.h tree.h Moves.h c_chess.h decision.h tree_stats.h
	$(CC) $(FLAGS) main.c -o main.o
main: main.o Legal.o Moves.o Board.o bitboard.o tree.o decision.o c_chess.o tree_stats.o
	gcc -g -Wall -std=c11 Legal.o bitboard.o tree_stats.o Board.o tree.o Moves.o decision.o c_chess.o main.o -lm -o main

main4.o: Constants.h Legal.h main4.c bitboard.c
	$(CC) $(FLAGS) main4.c -o main4.o
main4: main4.o Legal.o Board.o bitboard.o
	gcc -Wall -std=c11 Legal.o bitboard.o Board.o main4.o -lm -o main4

Test: main4.o Legal.o bitboard.o
	$(CC) -Wall -std=c11 Legal.o main.o bitboard.o -o main4

clean:
	rm main.o main4.o Legal.o Board.o bitboard.o tree_stats.o tree.o Moves.o main2.o main3.o decision.o Piece.o fail_nodep.txt fail_nodepp.txt fail_node.txt main main4 main2 main3 c_chess.o c_chess
