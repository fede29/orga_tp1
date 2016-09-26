#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char const* const fileName = argv[4]; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];
    unsigned int rows = (int)*argv[2];
    unsigned int cols = (int)*argv[3];
    unsigned int actionsCount = (int)*argv[1];
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned char board[rows][cols];

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s", line);
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

    loadBoard(board, file);

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
    			printResult(board, i);
    		}
    	}
    }

    return 0;
}


unsigned int vecinos (unsigned char *a, unsigned int i, unsigned int j, unsigned int m, unsigned int n){
	unsigned int neighbors = 0;

	if (((i + 1) <= m) && (a[i + 1][j] == '1')) {
		neighbors++;
	}

	if (((j + 1) <= n) && (a[i][j + 1] == '1')) {
		neighbors++;
	}

	if (((i + 1) <= m) &&  ((j + 1) <= n) && (a[i + 1][j + 1] == '1')) {
		neighbors++;
	}

	if (((i - 1) >= 0) && (a[i - 1][j] == '1')) {
		neighbors++;
	}

	if (((j - 1) >= 0) && (a[i][j - 1] == '1')) {
		neighbors++;
	}

	if (((i - 1) >= 0) &&  ((j - 1) >= 0) && (a[i - 1][j - 1] == '1')) {
		neighbors++;
	}

	if (((i + 1) <= m) &&  ((j - 1) >= 0) && (a[i + 1][j - 1] == '1')) {
		neighbors++;
	}

	if (((i - 1) >= 0) &&  ((j + 1) <= n) && (a[i - 1][j + 1] == '1')) {
		neighbors++;
	}

	return neighbors;
}

