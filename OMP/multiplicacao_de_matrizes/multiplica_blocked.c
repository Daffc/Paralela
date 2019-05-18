#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 2048 
#define NTHREADS 4
#define BLOCK 2
int main(){
	double * MA,* MB, * MC;
	
	MA = malloc(SIZE * SIZE * sizeof(double));
	MB = malloc(SIZE * SIZE * sizeof(double));
	MC = malloc(SIZE * SIZE * sizeof(double));
	
	
	for(int i= 0; i < SIZE; i++){
		for(int j= 0; j < SIZE; j++){
			MA[(i * SIZE) + j] = i /(j + 1.0);
			MB[(i * SIZE) + j] = i - j;
		}
	}
	int pos_i, pos_j;
	#pragma omp parallel for schedule(dynamic) default(shared) private(pos_i, pos_j)firstprivate(MA,MB,MC) num_threads(NTHREADS)	
	for(int ii= 0; ii < SIZE; ii += BLOCK){
		for(int jj= 0; jj< SIZE; jj+= BLOCK){
			for(int i= 0; i < BLOCK; i++){
       			for(int j= 0; j < BLOCK; j++){
					pos_i = i + ii;
					pos_j = j + jj;
           			MC[(i * SIZE) + j] = 0.0;
    			
					for(int k= 0; k < BLOCK; k++){
						MC[(pos_i * SIZE) + pos_j] += MA[(pos_i * SIZE) + k] * MB[(k * SIZE) + pos_j];
					} 
	   			}
    		}
		}
	}
	printf("%f", MC[((SIZE ) * (SIZE)) - 1]);	

}

