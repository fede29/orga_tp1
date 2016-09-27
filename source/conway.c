#include <stdlib.h>
#include <stdio.h>

unsigned int vecinos (unsigned char *a, unsigned int i, unsigned int j, unsigned int m, unsigned int n){
	unsigned int neighbors = 0;

	int iPlusOne = i + 1;
	int iMinusOne = i - 1;
	int jPlusOne = j + 1;
	int jMinusOne = j - 1;

	if ((iPlusOne <= m) && (a[(iPlusOne * n + j)] == '1')) {
		neighbors++;
	}
	
	if ((jPlusOne <= n) && (a[(i * n  + jPlusOne)] == '1')) {
		neighbors++;
	}

	if ((iPlusOne <= m) &&  (jPlusOne <= n) && (a[iPlusOne * n + jPlusOne] == '1')) {
		neighbors++;
	}

	if ((iMinusOne >= 0) && (a[iMinusOne * n + j] == '1')) {
		neighbors++;
	}

	if ((jMinusOne >= 0) && (a[i * n + jMinusOne] == '1')) {
		neighbors++;
	}

	if ((iMinusOne >= 0) &&  (jMinusOne >= 0) && (a[iMinusOne * n + jMinusOne] == '1')) {
		neighbors++;
	}

	if ((iPlusOne <= m) &&  (jMinusOne >= 0) && (a[iPlusOne * n + jMinusOne] == '1')) {
		neighbors++;
	}

	if ((iMinusOne >= 0) &&  (jPlusOne <= n) && (a[iMinusOne * n + jPlusOne] == '1')) {
		neighbors++;
	}

	return neighbors;
}

void loadBoard (char* fileName, unsigned char *a, unsigned int rows, unsigned int cols) {
	printf("start loading the file \n");
	FILE* file = fopen(fileName, "r");
	char line[4];

	while (fgets(line, 40, file) != NULL) {
		printf("reading line \n");
		printf("line readed %s", line);
		
		int i = line[0] - '0';
		int j = line[2] - '0';
		
		printf("line pos i  %i \n", i);
		printf("line pos j  %i \n", j);

		a[i * cols + j] = '1';
	}

	printf("end loading the file \n");

	fclose(file);
}

void loadBlankBoard (unsigned char *a, unsigned int rows, unsigned int cols) {
	unsigned int j = 0;
	unsigned int k = 0;

	for (j = 0; j <= rows; j++) {
		for (k = 0; k <= cols; k++) {
			a[j * cols + k] = '0';
		}
	}
}

void printBoard (unsigned char *a, unsigned int rows, unsigned int cols) {
	unsigned int j = 0;
	unsigned int k = 0;

	for (j = 0; j <= rows; j++) {
		for (k = 0; k <= cols; k++) {
			printf("%c ", a[j * cols + k]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {
	printf("start \n");
	char* fileName = argv[4];
	unsigned int rows = atoi(argv[2]);
	unsigned int cols = atoi(argv[3]);
	unsigned int actionsCount = atoi(argv[1]);
	printf("end loading parameters \n");

	printf("parameter 1 %i \n", actionsCount);
	printf("parameter 2 %i \n", cols);
	printf("parameter 3 %i \n", rows);
	printf("parameter 4 %s \n", fileName);

	printf("init the variables \n");
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned char board[rows][cols];
	printf("end the init of the variables \n");

	printf("start loading blank board to work \n");
	loadBlankBoard(board, rows, cols);
	printf("end loading blank board to work \n");
	printBoard(board, rows, cols);

	printf("start loading the board from file \n");
	loadBoard(fileName, board, rows, cols);
	printf("end load board from file \n");

	printBoard(board, rows, cols);
	
	for (i = 0; i <= actionsCount; i++) {
		printf("start the action %i \n", i);
		for (j = 0; j <= rows; j++) {
			for (k = 0; k <= cols; k++) {
				unsigned int neighbors = vecinos (board, j, k, rows, cols);

				if (((neighbors == 2) || (neighbors == 3)) && (board[j][k] == '1')) {
					board[j][k] = '1';
				}
				if ((board[j][k] == '0') && (neighbors == 3)) {
					board[j][k] = '1';
				}
				if ((neighbors < 2) || (neighbors > 3)) {
					board[j][k] = '0';
				}
			}
		}
		printBoard(board, rows, cols);
		printf("end the action %i \n", i);
	}
	
	return 0;
}

