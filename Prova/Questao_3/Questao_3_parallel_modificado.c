#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20000
#define BLOCK 128
#define NTHREADS 4
int main(){
    // Vetor, matrizA e MatrizResposta;
	double *V,*MA, * VR;
	int ii, i, jj, j;
	
	V = malloc(N * sizeof(double));
	MA = malloc(N * N * sizeof(double));
	VR = malloc( N * sizeof(double));
	
	
	for(i= 0; i < N; i++){
        V[i] = i;
        VR[i] = 0.0;
		for(j= 0; j < N; j++){
			MA[(i * N) + j] = (i/(j+1.0));
		}
	}

	#pragma omp parallel for schedule(dynamic) default(shared) private(jj, i, j) num_threads(NTHREADS)	
    for(ii = 0; ii < N; ii += BLOCK){
        for(jj = 0; jj< N; jj+= BLOCK){
            for(i= 0; i < BLOCK && (i + ii) < N; i++){
                for(j= 0; j < BLOCK && (j + jj) < N; j++){
                    VR[ii + i] += V[ii + i] * MA[((j + jj) * N) + (ii + i)];
                }
            }
        }
    }

	printf("%f\n", VR[N-1]);	
}

