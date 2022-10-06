#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <wchar.h>
#include <locale.h>

#define NTHREADS 1   
#define LETRAS 26
#define TAMANHO_BUFFER 16384

int *vet_count;

pthread_mutex_t mutex_arquivo;
pthread_mutex_t mutex_vetor;
FILE *arquivo;
void *le_arquivo(void *id);

int main(){
	setlocale(LC_ALL, "");

	pthread_t thread[NTHREADS];

    vet_count = malloc(LETRAS * sizeof(int));
    arquivo = stdin;

	for(int i = 0; i < NTHREADS; i++){
		vet_count[i] = 0;
	}

	for(int i = 0; i < NTHREADS; i++){ 
		pthread_create(&thread[i], NULL, le_arquivo,( void *) i);		
	}

    for(int i = 0; i < NTHREADS; i++){
       	pthread_join(thread[i], NULL);
	}
    
//	for(int i = 0; i < LETRAS; i++){
//    	printf("%C\t%d\n", i + 0x41, vet_count[i] );
//	}
	printf("%d\n", vet_count[LETRAS - 1]);
	free(vet_count);
	fclose(arquivo);
}

wchar_t * existe(wint_t * linha){
    wchar_t * retorno;
	pthread_mutex_lock(&mutex_arquivo);
        retorno = fgetws_unlocked(linha, TAMANHO_BUFFER, arquivo); 
    pthread_mutex_unlock(&mutex_arquivo);
	return retorno;
}

void *le_arquivo(void *id){
    wint_t * linha;
	wchar_t c;
	unsigned int posicao;
	unsigned int aux[LETRAS];
	
	memset(aux, 0, LETRAS * sizeof(unsigned int));	
	linha = malloc(TAMANHO_BUFFER * sizeof(wint_t));	

     while( existe(linha) != NULL){
        posicao = 0;
        c =linha[posicao];
		while(c != '\0'){
			if(linha[posicao] >= 0x41 && linha[posicao] <= 0x5a){
                c -=  0x41;
				aux[c] += 1;
			}
			else
				if(linha[posicao] >= 0x61 && linha[posicao] <= 0x7a){
                	c -=  0x61;
                	aux[c] += 1;
            	}

			c = linha[++posicao];
        }   
    }  	
	
	pthread_mutex_lock(&mutex_vetor);
		for(int i = 0; i < LETRAS; i++){
			vet_count[i] += aux[i];
		}	
	pthread_mutex_unlock(&mutex_vetor);
	free(linha);
    return NULL;
}
