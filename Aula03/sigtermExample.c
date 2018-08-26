//Based on  https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void signal_handler(int sigNumber)
{
  if (sigNumber == SIGTERM)
    printf("Recebi um SIGTERM\n");
}

int main(void)
{
  if (signal(SIGTERM, signal_handler) == SIG_ERR)
  	printf("\nNao consigo tratar SIGTERM\n");
  while(1) 
	sleep(1);
  return 0;
}
