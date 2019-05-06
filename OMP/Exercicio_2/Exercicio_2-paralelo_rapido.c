#include <omp.h>
#include <stdio.h>

#define NTHREADS 6

static long num_steps = 1000000000;

double step;

int main(){
	
	double pi, sum = 0.0;
	
	step = 1.0/ num_steps;
	
	#pragma omp parallel
	{	
		int i, id, offset;
		double x, s = 0;

		id = omp_get_thread_num();
		
		offset = omp_get_num_threads();

		for(i = id; i < num_steps; i+= offset){
		 	x = (i + 0.5) * step;
			
       		s = s  + (4.0 / (1.0 + x*x));
		}	
		#pragma omp atomic
			sum += s;
	}		

	pi = step * sum;
	printf("%f\n", pi);

}
