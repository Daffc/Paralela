#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define THREAD 8

int * resposta, *A, *B, tam;

void *soma_vet(void *);

int main(){
	pthread_t thread[THREAD];
	
	tam = 1 << 27;
	
	resposta = malloc(tam * sizeof(int));
	A = malloc(tam * sizeof(int));
	B = malloc(tam * sizeof(int));

	for(int i = 0; i < tam; i++){
		A[i] = i;
		B[i] = i;
		resposta[i] = 0;        	
	}

	for(int i = 0; i < 8; i++){
		pthread_create(&thread[i], NULL, soma_vet,( void *) i);		
	}	
        
	for(int i = 0; i < 8; i++){
        	pthread_join(thread[i], NULL);
	}
	
        //for(int i = 0; i < tam; i++){
                printf("%d\t", resposta[tam -1]);
        //}	
}


void *soma_vet(void *id){
	int area = tam / THREAD;
	int offset = area * ((int) id); 
        for(int i = 0; i < area; i++){
        	resposta[offset + i] = A[offset + i] + B[offset + i];
	}
	return NULL;
}
