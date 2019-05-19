#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <pthread.h>

#define NTHREADS 4
#define BLOCK 131072
#define SHIFT 65
#define ALFABETO 256

unsigned long letras[NTHREADS][ALFABETO];

void *leitor(void *id);

FILE * in;

int main (int argc, char **argv)
{
    pthread_t threads[NTHREADS];
    unsigned long count = 0;

    in = fopen (argv[1],"r");
    
    if(!in){
      exit(1);
    }

    for(int i = 0; i < NTHREADS; i++){
        pthread_create(&threads[i], NULL, leitor, (void *)i);	
    }
    
    for(int i = 0; i < NTHREADS; i++){
        pthread_join(threads[i], NULL);
        count += letras[i][65] + letras[i][97];
    }

    printf("%lu\n",count);
    
    fclose(in);
    return 0;
}

void *leitor(void *id){
    unsigned char buffer[BLOCK];
    unsigned long i, n_read;

    letras[(int) id][65] = 0;
    letras[(int) id][97] = 0;

    while(n_read = fread(buffer, sizeof(char), BLOCK, in)){
        i = 0;
        for(i; i < n_read; i++){
            letras[(int) id][buffer[i]]++;       
        }
    }
}