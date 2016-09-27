#include <stdlib.h>
#include <stdio.h>

unsigned char ** init_board(unsigned int rows, unsigned int cols){
	unsigned char** board = (unsigned char**)malloc(cols*sizeof(char*));
	for (int i = 0; i<cols; i++){
		board[i] = (unsigned char *) malloc(rows*sizeof(char*));
		for (int j = 0; j<rows; j++){
			board[i][j]='0';
		}
	}
	return board;
}

void load_board(unsigned char **board, unsigned int rows, unsigned int cols, FILE *file){
	int x,y;
	while (fscanf (file, "%i %i", &x, &y)!=EOF){
		if (x<cols||y<rows){
			board[x][y]='1';
		}
	}
}

void print_board(unsigned char **board, unsigned int rows, unsigned int cols){
	for (int i = 0; i<cols; i++){
		for (int j = 0; j<rows; j++){
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}

unsigned int vecinos_posta(unsigned char *a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
	unsigned int vecinos = 0;
	for (int x = -1; x<2; x++){
		for (int y = -1; y<2; y++){
			if (x+i>=0 && x+i<N && y+j>=0 && y+j<M){
				if ((!(i==0&&j==0)) && board[(x+i) + M*(y+j)] == '1'){
					vecinos++;
				}
			}
		}
	}
	return vecinos; 
}

unsigned int vecinos(unsigned char **board, unsigned int x, unsigned int y, unsigned int rows, unsigned int cols){
	unsigned int vecinos = 0;
	for (int i = -1; i<2; i++){
		for (int j = -1; j<2; j++){
			if (x+i>=0 && x+i<cols && y+j>=0 && y+j<rows){
				if ((!(i==0&&j==0)) && board[x+i][y+j] == '1'){
					vecinos++;
				}
			}
		}
	}
	return vecinos;
}
	
void copy_board(unsigned char **from, unsigned char **to, unsigned int rows, unsigned int cols){
	for (int i = 0; i<cols; i++){
		for (int j = 0; j<rows; j++){
			to[i][j] = from[i][j];
		}
	}
}

void process_board(unsigned char **board, unsigned int rows, unsigned int cols, unsigned int actionCount){
	printf ("starting action\n");
	unsigned char **thisBoard = init_board(rows, cols);
	copy_board(board,thisBoard,rows, cols);
	for (int i = 0; i < actionCount; i++){
		printf("Simulation number: %i\n\n", i);
		unsigned char **nextBoard = init_board(rows, cols);
		print_board(thisBoard,rows,cols);
		for (unsigned int x = 0; x < cols; x++){
			for (unsigned int y = 0; y < rows; y++){
				unsigned int neighbours = vecinos(thisBoard, x, y, rows, cols);
				if (thisBoard[x][y]=='1'){
					if (neighbours == 3 || neighbours == 2){nextBoard[x][y] = '1';}
				}else{
					if (neighbours == 3){nextBoard[x][y] = '1';}
				}
			}
		}
		copy_board(nextBoard,thisBoard,rows, cols);
		free_board(nextBoard);
	}
	free_board(thisBoard);
	
}

int free_board (unsigned int **board, unsigned int rows, unsigned int cols){
	for (int i = 0; i<cols; i++){
		free(board[i]);
	}
	free(board);
	return 0;
}

int main(int argc, char* argv[])
{
	char const *fileName;
	unsigned int actionsCount;
	unsigned int rows;
	unsigned int cols;
	unsigned char **board;
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
	board = init_board(rows, cols);
	
	printf("loading board\n");
	load_board(board, rows, cols, file);
	
	fclose(file);
	
	printf("printing board\n");
	print_board(board, rows, cols);
	
	process_board(board, rows, cols, actionsCount);
	
	free_board(board)
	
}
