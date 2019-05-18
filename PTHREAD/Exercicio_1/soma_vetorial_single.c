#include <stdio.h>
#include <stdlib.h>

int * resposta, *A, *B, tam;

int main(){
	
	tam = 1 << 27;
	
	resposta = malloc(tam * sizeof(int));
	A = malloc(tam * sizeof(int));
	B = malloc(tam * sizeof(int));

	for(int i = 0; i < tam; i++){
		A[i] = i;
		B[i] = i;
		resposta[i] = 0;        	
	}
	
	for(int i = 0; i < tam; i++){
		resposta[i] = A[i] + B[i];       	
	}
	
	printf("%d\n", resposta[tam -1]);
}
