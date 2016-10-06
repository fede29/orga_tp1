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