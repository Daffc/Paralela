#include <omp.h>
#include <stdio.h>

static long num_steps = 1000000000;

double step;

int main(){
	
	double pi, somador[16], sum = 0.0;
	
	step = 1.0/(double) num_steps;
	
	for(int j = 0; j < 16; j++){
		somador[j]= 0;
	}
	#pragma omp parallel
	{	
		int i, id, offset;
		double x;
	
		id = omp_get_thread_num();
		
		offset = omp_get_num_threads();

		for(i = id; i < num_steps; i+= offset){
		 	x = (i + 0.5) * step;
			
       		somador[id] = somador[id]  + (4.0 / (1.0 + x*x));
		}	
	}		
	
    for(int j = 0; j < 16; j++){
        sum+= somador[j];
    }

	pi = step * sum;
	printf("%f\n", pi);

}
