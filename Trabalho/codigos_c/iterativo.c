#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h>

double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

int nao_valido(char * tabuleiro, int linha, int coluna) 
{ 
	int retorno = 0,  i, j; 

	// Verifica existência de rainhas na lateral e diagonais à esquerdas.
	for (i = coluna - 1; i >= 0; i--) 
		if (tabuleiro[i] == linha || (abs(tabuleiro[i] - linha) == coluna - i))
            return 1;
	return 0; 
} 


int resolve_tabuleiro(char * tabuleiro, int rainhas) 
{
	int solucoes = 0, coluna = 0, linha = 0;

    // Enquanto não encontrou distribuição válida ou não é possível voltar mais colunas no tabuleiro.
	while ((coluna >= 0)){

        // Percorre doas as linhas da rainha atual até que suas linhas se 
        // esgotem ou que posição válida seja encontrada.
        while ((linha < rainhas) && nao_valido(tabuleiro, linha, coluna))
            linha ++;
        
        // Caso linha válida seja encontrada, salvar posição da rainha.    
        if ( linha < rainhas ){ 
            tabuleiro[coluna] = linha; 
            
            // Avança para proxima rainha.
            coluna ++;

            // Caso tenha achado posição válida e seja a última rainha, 
            // somar solução e voltar a analizar ultima rainha em pŕoxima linha.
            if(coluna == rainhas){
                // Solução encontrada
                solucoes ++;
                coluna --;
                linha ++;
            }
            else{
                // Retorna linha para posição incial (nova rainha será analizada).
                linha = 0;                
            }
        }
        // Caso não tenha achado posição valida, backtrak.
        else{

            // Retorna à rainha anterior.
            coluna --;
            // Avanaça linha da rainha anterior.
            linha = tabuleiro[coluna] + 1;
        }      

	} 

    return solucoes;
} 

int main(int argc, char *argv[]) 
{ 
    int     rainhas;
    double  tempo;
    char * tabuleiro;
    tempo = timestamp();
    if (argc <= 1 || (rainhas = atoi(argv[1])) <= 0) 
	    rainhas = 4;

    // aloca espaço para N rainhas  + 1 (borda para efetuar operação em resolve_tabuleiro)
    tabuleiro = malloc((rainhas + 1) * sizeof(char)); 
    

    // Verifica se houve solução do problema.
	resolve_tabuleiro(tabuleiro + 1, rainhas); 

    tempo = timestamp() - tempo;

    printf("%d\t %.5f\t\n",rainhas, tempo);

    return 0;
} 
