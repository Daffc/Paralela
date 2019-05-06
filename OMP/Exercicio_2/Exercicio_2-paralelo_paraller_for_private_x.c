#include <stdio.h>
#include <omp.h>

#define NTHREADS 4
static long num_steps = 1000000000 ;

double step;

int main(){
	long i; 
	double pi, sum, x;
	
	step = 1.0/(double) num_steps;
		
	#pragma omp for schedule(static) reduction (+:sum)	private(x)
	for(i = 0; i < num_steps; i++){
		x = (i + 0.5) * step;
		sum += (4.0 / (1.0 + x*x));
	}

	pi = step * sum;
	printf("%lf\n", pi);
}
