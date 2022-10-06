#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

#define NTHREADS 6

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  =  malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     
	 int nNodes = 0, block;
	 void * pointers[NTHREADS + 1]; 

	 printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
     p = init_list(p);
     head = p;
	 //Count number of nodes.
	 while (p != NULL) {
 		nNodes++;
        p = p->next;
	 }
	 p = head;
	 block = nNodes/NTHREADS;  
    
     // Divide domain between workers according with the blocksize.
	 for(int i = 0; i < nNodes; i++)
	 {
		if(i%block == 0){
			pointers[i/block] = p;
		}
   		p = p->next;
	 }	
     // Define last pointer as NULL (stop condition of last worker).
	 pointers[NTHREADS] = NULL;
	 start = omp_get_wtime();
     {
		#pragma omp parallel num_threads(NTHREADS) private(p)
		{
			int id = omp_get_thread_num();
			void * stop = pointers[id + 1];
			p = pointers[id];
			
			// Begin to work in first node of worker blocksize until the begin of the next block (or NULL)
        	while (p != stop) {
		   		processwork(p);
		   		p = p->next;
        	}
		}
     }

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}
