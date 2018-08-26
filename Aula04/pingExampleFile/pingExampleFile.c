#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(void){
	FILE *stream;
	pid_t child_pid = fork();
	if (child_pid == 0) {
		//Run ping command
		stream = fopen("/tmp/saida.out", "w");
		dup2(fileno(stream), fileno(stdout));
		execlp("/bin/ping","ping","8.8.8.8","-c","50",NULL);
		fclose(stream);
		return 0;
	} 
	else {
		wait(NULL);
		printf("Task is done\n");
		return 0;
	}
}
