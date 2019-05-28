#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20000
#define NTHREADS 4
int main(){
    // Vetor, matrizA e MatrizResposta;
	double *V,*MA, * VR;
	int i, j;
	
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

	#pragma omp parallel for schedule(dynamic) default(shared) private(j) num_threads(NTHREADS)	
    for(i= 0; i < N; i++){
        for(j= 0; j < N; j++){
            VR[i] += V[i] * MA[(j * N) + i];
        }
    }
    // for(int i= 0; i < N; i++){
    //     for(int j= 0; j < N; j++){
	// 		printf("%f\t", MA[(i * N) + j]);
	// 	}
    //     printf("\n");
	// }
	printf("%f\n", VR[N-1]);	

}

