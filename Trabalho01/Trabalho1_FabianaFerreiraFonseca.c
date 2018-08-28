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

/*Declaracao da funcao para Tratamento de strings*/
int getArgumentsFromCommand(char*, char**);


/*Função que vai fazer o parser da string que vem da linha de comando, para pegar os argumentos inseridos*/
int getArgumentsFromCommand (char* command, char** arguments) 
{
	char* subString;
	unsigned counter = 1;
	subString = strtok(command, DELIMITER);
	arguments[counter - 1] = subString; 
	while (subString != NULL) {
		subString = strtok(NULL,DELIMITER);
		arguments[counter] = subString;
		counter++;
	}
	/*NULL é adicionado no final para que a chamada ao exec funcione*/
	arguments[counter + 1] = NULL;
	return 0;
}

void signal_handler(int sigNumber) {
	if (sigNumber == SIGUSR1)
		printf("recebi um sigterm\n");
}

/*-------------------------------------------------MAIN--------------------------------------------------*/
int main () 
{	
	char userInput [BUFFER];
	/*Alocando memoria para criar o array que armarezará os argumentos*/
	char** arguments = (char**)malloc(BUFFER*sizeof(char*));
	unsigned exit = 0;
	printf("\n/******************************************************************************/\n");
	printf("/*------ FABITS SHELL: UM SHELL SIMPLIFICADO PARA SISTEMAS OPERACIONAIS ------*/\n");
	printf("/******************************************************************************/\n");
	printf("\n");
	printf("\n");
	while (!exit) {
		printf("$fabitsShell ");
		while (1) {
			if (fgets(userInput, BUFFER, stdin) != NULL) {
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
					pid_t child_pid = fork();
					if (child_pid == 0) {
					/*Executa o comando pedido pelo usuario*/
						//stream = fopen("/tmp/saida.out", "w");
						//dup2(fileno(stream), fileno("stdout"));
						execv(commandPath, arguments);
						free(commandPath);
						break;
					}
					else {
						wait(NULL);
						printf("Task is done\n");
						break;
					}
				}
				else {
					exit = 1;					
					printf("Saindo do shell. Obrigada por testar!\n");
					break;
				}
				/*Tratar sinal para kill no processo*/
				if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
					printf("\nnao trato sigterm\n");
				}
				else 
					printf("tratei sigterm\n");
			
			}
		}
	}	
	free(arguments);
	return 0;
}
