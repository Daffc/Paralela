#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20000
#define NTHREADS 4
int main(){
    // Vetor, matrizA e MatrizResposta;
	double *V,*MA, * VR;
	
	V = malloc(N * sizeof(double));
	MA = malloc(N * N * sizeof(double));
	VR = malloc( N * sizeof(double));
	
	
	for(int i= 0; i < N; i++){
        V[i] = i;
        VR[i] = 0.0;
		for(int j= 0; j < N; j++){
			MA[(i * N) + j] = (i/(j+1.0));
		}
	}

	// #pragma omp parallel for schedule(dynamic) default(shared) private(pos_i, pos_j)firstprivate(MA,MB,MC) num_threads(NTHREADS)	
    for(int i= 0; i < N; i++){
        for(int j= 0; j < N; j++){
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

