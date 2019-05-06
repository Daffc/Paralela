#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wchar.h>
#include <locale.h>

#define NTHREADS 6 
#define LETRAS 26
#define TAMANHO_BUFFER 2048

int *vet_count;

pthread_mutex_t *mutex_vet;
pthread_mutex_t mutex_arquivo;

FILE *arquivo;

void *le_arquivo(void *id);

int main(){

	setlocale(LC_ALL, "");

	pthread_t thread[NTHREADS];

    mutex_vet =  malloc(LETRAS * sizeof(pthread_mutex_t));
    
    for(int i = 0; i < LETRAS; i++){

        pthread_mutex_init(&mutex_vet[i], NULL);
    }
	
    pthread_mutex_init(&mutex_arquivo, NULL);
    vet_count = malloc(LETRAS * sizeof(int));

    arquivo = fopen("Pride_and_Prejudice.txt", "r");
	
	if (!arquivo)
    {
		printf ("Erro na abertura do arquivo. Fim de programa.\n");
		exit (1);
	}	
	
	for(unsigned int i = 0; i < NTHREADS; i++){ 
		pthread_create(&thread[i], NULL, le_arquivo,( void *) arquivo);		
	}

    for(int i = 0; i < NTHREADS; i++){
       	pthread_join(thread[i], NULL);
	}
    for(int i = 0; i < LETRAS; i++){
    	printf("%C\t%d\n", i + 0x41, vet_count[i] );
	}

	fclose(arquivo);
}

wchar_t * existe(wint_t * linha, FILE * arquivo){
    wchar_t * retorno;
	pthread_mutex_lock(&mutex_arquivo);
        retorno = fgetws_unlocked(linha, TAMANHO_BUFFER, arquivo); 
    pthread_mutex_unlock(&mutex_arquivo);
	return retorno;
}

void *le_arquivo(void *arquivo){
    wint_t * linha;
	wchar_t c;
	unsigned int posicao;
	
	linha = malloc(TAMANHO_BUFFER * sizeof(wint_t));	

     while( existe(linha, (FILE * ) arquivo) != NULL){
        posicao = 0;
        c =linha[posicao];
		while(c != '\0'){
			if(linha[posicao] >= 0x41 && linha[posicao] <= 0x5a){
                c -=  0x41;
				pthread_mutex_lock(&mutex_vet[c]);
				vet_count[c] += 1;
				pthread_mutex_unlock(&mutex_vet[c]);
			}
			else
				if(linha[posicao] >= 0x61 && linha[posicao] <= 0x7a){
                	c -=  0x61;
                	pthread_mutex_lock(&mutex_vet[c]);
                	vet_count[c] += 1;
                	pthread_mutex_unlock(&mutex_vet[c]);
            	}

			c = linha[++posicao];
        }   
     }  	
	free(linha);
    return NULL;
}
