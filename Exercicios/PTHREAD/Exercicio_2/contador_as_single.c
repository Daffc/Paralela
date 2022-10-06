#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main (int argc, char **argv)
{
  // setlocale(LC_ALL, "en_US.UTF-8");
  FILE * in;
  char wc;
  unsigned long count = 0;
  in = fopen (argv[1],"r");
  
  if(!in){
	  exit(1);
  }
  
  while((wc=fgetc(in))!=EOF){
      if(wc == 'a' || wc == 'A')
			  count ++;
  }

  printf("%lu\n",count);
  
  fclose(in);
  return 0;
}