#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void writePBM(unsigned char** board, unsigned int dimx, unsigned int dimy, const char* fileName, unsigned int actionNumber)
{
	int i, j;
	int actionNumberStringLenght = 1;
	if (actionNumber >= 10){
		actionNumberStringLenght = 2;
	}
	char str[actionNumberStringLenght];
	sprintf(str, "%d", actionNumber);
	char newFileName[50];
	newFileName[0]='\0';
	strcat(newFileName,"imagenes/");
	strcat(newFileName,fileName);
	strcat(newFileName,"_");
	strcat(newFileName,str);
	strcat(newFileName,".pbm");

	FILE *fp = fopen(newFileName, "wb");
	if (fp==NULL){
		fprintf(stderr, "Error while opening output file: %s\n",newFileName);
		exit(1);
	}
	
	unsigned int amp = 3;
	(void) fprintf(fp, "P4\n%d %d\n", dimy*amp, dimx*amp);
	for (j = 0; j < dimy; ++j){
		for (i = 0; i < dimx; ++i)
		{
			//printf("board %c \n", board[i][j]);
			unsigned int x,y;
			unsigned char writeValue = 0;
			if ((board[i][j]) == '1'){
				writeValue = 1;
			}
			for (x = i*amp; x < amp*(i+1); x++){
				for (y = j*amp; y < amp*(j+1); y++){
					fprintf(fp, "%c", writeValue);
				}
			}
			//(void) fwrite(&writeValue, 1, sizeof(unsigned char), fp);
		}
	}
	(void) fclose(fp);
	return;
}


unsigned char ** init_board(unsigned int rows, unsigned int cols){
	unsigned char** board = (unsigned char**)malloc(cols*sizeof(char*));
	unsigned int i,j;
	for (i = 0; i<cols; i++){
		board[i] = (unsigned char *) malloc(rows*sizeof(char*));
		for (j = 0; j<rows; j++){
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


int free_board (unsigned char **board, unsigned int rows, unsigned int cols){
	unsigned int i;
	for (i = 0; i<cols; i++){
		free(board[i]);
	}
	free(board);
	return 0;
}


void print_board(unsigned char **board, unsigned int rows, unsigned int cols){
	unsigned int i,j;
	for (i = 0; i<cols; i++){
		for (j = 0; j<rows; j++){
			//printf("%c",board[i][j]);
			if (board[i][j] == '0'){
				printf("·");
			}else{
				printf("O");
			}
		}
		printf("\n");
	}
}


unsigned char* board_to_array(unsigned char ** board, unsigned int rows, unsigned int cols){
	unsigned char* array = (unsigned char*)malloc(sizeof(char*)*rows*cols);
	int x,y;
	for (x=0; x<cols; x++){
		for (y=0; y<rows; y++){
			unsigned int pos = cols*x+y;
			array[pos]=board[x][y];
		}
	}
	return array;
}


unsigned int vecinos(unsigned char *a, unsigned int i, unsigned int j, unsigned int M, unsigned int N){
	unsigned int vecinos = 0;
	int x,y;
	for (x = -1; x<2; x++){
		for (y = -1; y<2; y++){
			if (x+i>=0 && x+i<N && y+j>=0 && y+j<M){
				if ((!(x==0&&y==0)) && a[N*(x+i) + (y+j)] == '1'){
					vecinos++;
				}
			}
		}
	}
	return vecinos;
}


unsigned int vecinos_m(unsigned char **board, unsigned int x, unsigned int y, unsigned int rows, unsigned int cols){
	unsigned int vecinos = 0;
	int i,j;
	for (i = -1; i<2; i++){
		for (j = -1; j<2; j++){
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
	unsigned int i,j;
	for (i = 0; i<cols; i++){
		for (j = 0; j<rows; j++){
			to[i][j] = from[i][j];
		}
	}
}


void process_board(unsigned char **board, unsigned int rows, unsigned int cols, unsigned int actionCount,const char* fileName){
	printf ("starting action\n");
	unsigned char **thisBoard = init_board(rows, cols);
	copy_board(board,thisBoard,rows, cols);
	unsigned int i,x,y;
	for (i = 0; i < actionCount; i++){
		printf("Simulation number: %i\n\n", i);
		unsigned char **nextBoard = init_board(rows, cols);
		print_board(thisBoard,rows,cols);
		writePBM(thisBoard, rows, cols, fileName, i);
		for (x = 0; x < cols; x++){
			for (y = 0; y < rows; y++){
				unsigned char * array = board_to_array(thisBoard, rows, cols);
				unsigned int neighbours = vecinos(array, x, y, rows, cols);
				free(array);
				//unsigned int neighbours = vecinos_m(thisBoard,x,y,rows,cols);
				//printf("vecinos para celda (%i,%i): %i\n", x, y, neighbours);
				if (thisBoard[x][y]=='1'){
					if (neighbours == 3 || neighbours == 2){nextBoard[x][y] = '1';}
				}else{
					if (neighbours == 3){nextBoard[x][y] = '1';}
				}
			}
		}
		copy_board(nextBoard,thisBoard,rows, cols);
		free_board(nextBoard, rows, cols);
	}
	free_board(thisBoard, rows, cols);
}


void print_help(){
	printf("Uso:\n");
	printf("  conway -h\n  conway -V\n  conway i M N inputfile [-o outputprefix]\n");
	printf("Opciones:\n");
	printf("  -h, --help    Imprime este mensaje\n");
	printf("  -V, --version Da la version del programa\n");
	printf("  -o            Prefijo de los archivos de salida\n");
	printf("Ejemplos: \n");
	printf("  conway 10 20 20 glider -o estado\n");
	printf("  Representa 10 iteraciones del Juego de la Vida en una Matriz\n");
	printf("  de 20x20, con un estado inicial tomado del archivo ''glider''.\n");
	printf("  Los archivos de salida se llamarán estado_n.pbm,\n");
	printf("  si no se da un prefijo para el archivo de salida, \n");
	printf("  el prefijo será el nombre del archivo de entrada.\n");
}

void print_version (){
	printf("Conway -Game of Life- version: 1.0\n");
}
	
void validate_actionsCount(int actionsCount){
	if (actionsCount <= 0){
		fprintf(stderr, "Actions Count must be a positive integer!\n");
		exit(1);
	}
}

void validate_rows(int rows){
	if (rows <= 0){
		fprintf(stderr, "Number of rows must be a positive integer!\n");
		exit(1);
	}
}
	
void validate_cols(int cols){
	if (cols <= 0){
		fprintf(stderr, "Number of columns must be a positive integer!\n");
		exit(1);
	}
}
	
int main(int argc, char* argv[])
{
	char const *fileName;
	char const *outputFileName;
	unsigned int actionsCount;
	unsigned int rows;
	unsigned int cols;
	unsigned char **board;
	//asigno valores de parametros
	if (argc == 2){
		char* arg = argv[1];
		if (strcmp(arg,"-h") == 0 || strcmp(arg,"--help") == 0){
			print_help();
			return 0;
		}
		else if (strcmp(arg,"-v") == 0 || strcmp(arg,"--version") == 0){
			print_version();
			return 0;
		}
		else{
			fprintf(stderr,"Invalid parameter!\n");
			exit(1);
		}
	}else if (argc != 5 && argc != 7){ //ver
		fprintf(stderr,"Wrong number of parameters!\n");
		exit(1);
	}else{
		fileName = argv[4];
		actionsCount = (int) atoi(argv[1]);
		validate_actionsCount(actionsCount);
		rows = (int) atoi(argv[2]);
		validate_rows(rows);
		cols = (int) atoi(argv[3]);
		validate_cols(cols);
		outputFileName = fileName;
		if (argc == 7){
			if (strcmp(argv[5],"-o") == 0){
				outputFileName = argv[6];
			}else{
				fprintf(stderr,"Invalid parameter!\n");
				exit(1);
			}
		}
	}
	printf("filename: %s\n", fileName);
	printf("count: %i\n", actionsCount);
	printf("rows: %i\n", rows);
	printf("cols: %i\n", cols);
	printf("outputFileName: %s\n", outputFileName);

	//abro mi archivo
	printf("Abriendo archivo\n");
	FILE* file = fopen(fileName, "r");
	if (file==NULL){
		fprintf(stderr, "Error while opening input file\n");
		exit(1);
	}
	
	printf("iniciando board\n");
	board = init_board(rows, cols);

	printf("loading board\n");
	load_board(board, rows, cols, file);

	fclose(file);

	/*printf("printing board\n");
	print_board(board, rows, cols);*/

	process_board(board, rows, cols, actionsCount, outputFileName);
	
	free_board(board, rows, cols);
	
	return 0;
}
