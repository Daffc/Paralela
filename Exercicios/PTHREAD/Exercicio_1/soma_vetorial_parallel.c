#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4

int * resposta, *A, *B, tam;

void *somador(void *);


int main(){
	
	tam = 1 << 27;

	pthread_t threads[NTHREADS];
	
	resposta = malloc(tam * sizeof(int));
	A = malloc(tam * sizeof(int));
	B = malloc(tam * sizeof(int));
	
	for(int i = 0; i < NTHREADS; i++){
		pthread_create(&threads[i], NULL, somador, (void *)i);	
	}
	
	for(int i = 0; i < NTHREADS; i++){
		pthread_join(threads[i], NULL);	
	}

	printf("%d\n", resposta[tam -1]);
}

void *somador(void *id){
	
	int maximo = tam/NTHREADS, inicio = maximo * (int ) id;

	maximo += inicio;

	for(inicio; inicio < maximo; inicio ++){
		A[inicio] = inicio;
		B[inicio] = inicio;
		resposta[inicio]= 0;
		resposta[inicio] = A[inicio] + B[inicio];
	}
}