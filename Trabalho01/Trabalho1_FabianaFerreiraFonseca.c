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
	char* teste = malloc(sizeof(char*));
	strcpy(teste,"oi tudo bem");
	printf("%s\n",teste);
	getArgumentsFromCommand(teste);
	free(teste);
	return 0;
}
