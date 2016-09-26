#include <stdlib.h>
#include <stdio.h>

unsigned int ** init_board(unsigned int rows, unsigned int cols, FILE *file){
	unsigned int** board = (unsigned int**)malloc(cols*sizeof(int*));
	for (int i = 0; i<cols; i++){
		board[i] = (unsigned int *) malloc(rows)
		for (int j = 0; j<rows; j++){
			board[i][j]=0;
		}
	}
	return board;
}
	

void print_board(unsigned int **board, unsigned int rows, unsigned int cols){
	for (int i = 0; i<rows; i++){
		for (int j = 0; j<cols; j++){
			printf("a");
		}
		printf("\n");
	}
}


int main(int argc, char* argv[])
{
	char const *fileName;
	unsigned int actionsCount;
	unsigned int rows;
	unsigned int cols;
	unsigned int **board;
	//asigno valores de parametros
	if (argc != 5){
		fprintf(stderr,"Wrong number of parameters!\n");
		exit(1);
	}else{
		fileName = argv[4];
		actionsCount = (int) atoi(argv[1]);
		rows = (int) atoi(argv[2]);
		cols = (int) atoi(argv[3]);
	}
	//abro mi archivo
	FILE* file = fopen(fileName, "r");
	if (file==NULL){
		fprintf(stderr, "Error while opening file\n");
		exit(1);
	}
	
	board = init_board(rows, cols, file);
	
	print_board(board, rows, cols);
	
	printf("%s\n", fileName);
	printf("count: %i\n", actionsCount);
	printf("rows: %i\n", rows);
	printf("cols: %i\n", cols);
	
}
