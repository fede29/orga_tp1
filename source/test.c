#include <stdlib.h>
#include <stdio.h>

void read_file(FILE *file){
	int x;
	int y;
	while (fscanf(file,"%i %i", &x, &y)!=EOF){
		printf("x: %i, y: %i\n",x,y);
	}
}

unsigned int ** init_board(unsigned int rows, unsigned int cols, FILE *file){
	unsigned int** board = (unsigned int**)malloc(cols*sizeof(int*));
	for (int i = 0; i<cols; i++){
		board[i] = (unsigned int *) malloc(rows*sizeof(int*));
		for (int j = 0; j<rows; j++){
			board[i][j]=0;
		}
	}
	return board;
}

void load_board(unsigned int **board, unsigned int rows, unsigned int cols, FILE *file){
	int x,y;
	while (fscanf (file, "%i %i", &x, &y)!=EOF){
		if (x<cols||y<rows){
			board[x][y]=1;
		}
	}
}

void print_board(unsigned int **board, unsigned int rows, unsigned int cols){
	for (int i = 0; i<cols; i++){
		for (int j = 0; j<rows; j++){
			printf("%i",board[i][j]);
		}
		printf("\n");
	}
}

int free_board (unsigned int **board, unsigned int rows, unsigned int cols){
	//liberar memoria del board
	return 0;
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
	
	printf("filename: %s\n", fileName);
	printf("count: %i\n", actionsCount);
	printf("rows: %i\n", rows);
	printf("cols: %i\n", cols);
	
	//abro mi archivo
	printf("Abriendo archivo\n");
	FILE* file = fopen(fileName, "r");
	if (file==NULL){
		fprintf(stderr, "Error while opening file\n");
		exit(1);
	}
	
	printf("iniciando board\n");
	board = init_board(rows, cols, file);
	
	printf("loading board\n");
	load_board(board, rows, cols, file);
	
	fclose(file);
	
	printf("printing board\n");
	print_board(board, rows, cols);
	
}
