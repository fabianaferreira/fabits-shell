/*Universidade Federal do Rio de Janeiro
  Departamento de Engenharia Eletrôncia e de Computação
  Sistemas Operacionas - 2018.2
  Aluna: Fabiana Ferreira Fonseca
  DRE: 115037241*/

/*TRABALHO 1: IMPLEMENTAÇÃO DE UM SHELL PARA LINUX*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EOS	"\0"
#define BUFFER	100
#define DELIMITER " "
#define EXIT_COMMAND "exit"

/*Declaracao da funcao para Tratamento de strings*/
int getArgumentsFromCommand(char*);


/*Função que vai fazer o parser da string que vem da linha de comando, para pegar os argumentos inseridos*/
int getArgumentsFromCommand (char* command) 
{
	char* subString;
	subString = strtok(command, DELIMITER);
	while (subString != NULL) {
		printf("%s\n",subString);
		subString = strtok(NULL,DELIMITER);
	}
	return 0;
}

/*-------------------------------------------------MAIN--------------------------------------------------*/
int main () 
{	
	char userInput [BUFFER];
	unsigned exit = 0;
	printf("\n/******************************************************************************/\n");
	printf("/*------ FABITS SHELL: UM SHELL SIMPLIFICADO PARA SISTEMAS OPERACIONAIS ------*/\n");
	printf("/******************************************************************************/\n");
	printf("\n");
	printf("\n");
	printf("$fabitsShell ");
	while (!exit) {
		while (1) {
			fgets(userInput, BUFFER, stdin);
			if (strlen(userInput) > 0 && !strcmp(userInput,EXIT_COMMAND)) 
			{
				printf("Input: %s\n", userInput);
				/*Trata e faz o parser da string recebida na linha de comando*/
				getArgumentsFromCommand(userInput);
				break;
			}
			else {
				exit = 1;
				printf("Saindo do fabitsShell\n");
				break;
			}
		}
	}

	
	return 0;
}
