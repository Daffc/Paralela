#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 2048 
#define NTHREADS 4
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
			for(int i= 0; i < SIZE; i++){
       			for(int j= 0; j < SIZE; j++){
           			MC[(i * SIZE) + j] = 0.0;
					for(int k= 0; k < SIZE; k++){
						MC[(i * SIZE) + j] += MA[(i * SIZE) + k] * MB[(k * SIZE) + j];
					} 
	   			}
    		}
	printf("%f", MC[((SIZE ) * (SIZE)) - 1]);	

}

