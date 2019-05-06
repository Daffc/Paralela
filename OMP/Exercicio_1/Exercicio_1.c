#include <stdio.h>
#include <omp.h>

int main(){
	int ID = 0;

	#pragma omp parallel 
	{
		printf("hello(%d)", omp_get_thread_num());
		printf("word(%d)\n", omp_get_thread_num());
	}
}
