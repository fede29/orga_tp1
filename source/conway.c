#include <stdlib.h>
#include <stdio.h>

/*
void multi_by_minus(float *matrix, int nRows, int nCols) {
  short i,j;
  for (i = 0; i < nRows; i++) {
      for (j = 0; j < nCols; j++) {
          matrix[i * nCols + j] *= -1;
      }
  }
}*/

unsigned int vecinos (unsigned char *a, unsigned int i, unsigned int j, unsigned int m, unsigned int n){
	unsigned int neighbors = 0;

	if (((i + 1) <= m) && (a[i + 1 * n + j] == '1')) {
		neighbors++;
	}

	if (((j + 1) <= n) && (a[i * n  + j + 1] == '1')) {
		neighbors++;
	}

	if (((i + 1) <= m) &&  ((j + 1) <= n) && (a[i + 1 * n + j + 1] == '1')) {
		neighbors++;
	}

	if (((i - 1) >= 0) && (a[i - 1 * n + j] == '1')) {
		neighbors++;
	}

	if (((j - 1) >= 0) && (a[i * n + j - 1] == '1')) {
		neighbors++;
	}

	if (((i - 1) >= 0) &&  ((j - 1) >= 0) && (a[i - 1 * n + j - 1] == '1')) {
		neighbors++;
	}

	if (((i + 1) <= m) &&  ((j - 1) >= 0) && (a[i + 1 * n + j - 1] == '1')) {
		neighbors++;
	}

	if (((i - 1) >= 0) &&  ((j + 1) <= n) && (a[i - 1 * n + j + 1] == '1')) {
		neighbors++;
	}

	return neighbors;
}

void loadBoard (char* fileName, unsigned char **board ) {
	printf("start loading the file \n");
	FILE* file = fopen(fileName, "r");
	char line[2];

	while (fgets(line, sizeof(line), file)) {
		printf("reading line \n");
		int i = line[0] - '0';
		int j = line[0] - '0';

		board[i][j] = '1';
	    printf("%s", line);
	}

	printf("end loading the file \n");

	fclose(file);
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

	printf("start loading the board from file \n");
	loadBoard(fileName, board);
	printf("end load board from file \n");
	printf("start the action \n");
	for (i = 0; i <= actionsCount; i++) {
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
				//printResult(board, i);
				printf("doing the action \n");
			}
		}
	}

	return 0;
}