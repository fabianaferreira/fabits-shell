/*Universidade Federal do Rio de Janeiro
  Departamento de Engenharia Eletrôncia e de Computação
  Sistemas Operacionas - 2018.2
  Aluna: Fabiana Ferreira Fonseca
  DRE: 115037241*/

/*TRABALHO 1: IMPLEMENTAÇÃO DE UM SHELL PARA LINUX*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define EOS	"\0"
#define BUFFER	100
#define DELIMITER " "
#define EXIT_COMMAND "exit"
#define PATH "/bin/"
#define CYAN_COLOR	"\033[1;36m"
#define GREEN_COLOR	"\033[1;32m"
#define RESET_COLOR "\033[0m"


/*Declaracao da funcao para Tratamento de strings*/
int getArgumentsFromCommand(char*, char**);
void signal_handler(int);

/*Função que vai fazer o parser da string que vem da linha de comando, para pegar os argumentos inseridos*/
int getArgumentsFromCommand (char* command, char** arguments) 
{
	char* subString;
	unsigned counter = 1;
	subString = strtok(command, DELIMITER);
	arguments[counter - 1] = subString; 
	while (subString != NULL) 
	{
		subString = strtok(NULL,DELIMITER);
		arguments[counter] = subString;
		counter++;
	}
	/*NULL é adicionado no final para que a chamada ao exec funcione*/
	arguments[counter + 1] = NULL;
	return 0;
}

pid_t child_pid;

void signal_handler(int sigNumber) 
{
	if (sigNumber == SIGUSR1 && child_pid != getpid()) 
	{	
		printf("Recebi um sinal de SIGUSR1. Terminando processo criado.\n");
		kill(child_pid, SIGUSR1);
	}
}

/*-------------------------------------------------MAIN--------------------------------------------------*/
int main () 
{	
	char userInput [BUFFER];
	/*Alocando memoria para criar o array que armarezará os argumentos*/
	char** arguments = (char**)malloc(BUFFER*sizeof(char*));
	unsigned exit = 0;
	printf(CYAN_COLOR);
	printf("\n/******************************************************************************/\n");
	printf("/*------ FABITS SHELL: UM SHELL SIMPLIFICADO PARA SISTEMAS OPERACIONAIS ------*/\n");
	printf("/******************************************************************************/\n");
	printf(RESET_COLOR);
	printf("\n");
	printf("\n");
	while (!exit) 
	{
		printf(GREEN_COLOR);
		printf("$fabitsShell: ");
		printf(RESET_COLOR);
		signal(SIGUSR1, signal_handler);
		if (fgets(userInput, BUFFER, stdin) != NULL) 
		{
			/*Tratando a retirada do caracter de retorno que vem com a chamada da fgets*/
			unsigned inputLength = strlen(userInput);
			if (inputLength > 0 && userInput[inputLength - 1] == '\n')
				userInput[--inputLength] = '\0';
				/*Entrou com um comando que não é o exit*/
			if (strcmp(userInput,EXIT_COMMAND) != 0) 
			{
			/*Trata e faz o parser da string recebida na linha de comando*/
				getArgumentsFromCommand(userInput,arguments);
				char* commandPath = (char*)malloc(sizeof(char*));
				strcpy(commandPath, PATH);
				strcat(commandPath,arguments[0]);
				child_pid = fork();
				if (child_pid == 0) 
				{
				/*CHILD*/
				/*Executa o comando pedido pelo usuario*/
					//stream = fopen("/tmp/saida.out", "w");
					//dup2(fileno(stream), fileno("stdout"));
					execv(commandPath, arguments);
				}
				else 
				{
				/*PARENT*/
					wait(NULL);						
				}					
				free(commandPath);
			}
			else 
			{
				exit = 1;					
				printf("Saindo do shell. Obrigada por testar!\n");
			}			
		}
	}	
	free(arguments);
	return 0;
}
