#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "consts.h"
#include "functions.h"

/*Função que vai fazer o parser da string que vem da linha de comando, para pegar os argumentos inseridos*/
int getArgumentsFromCommand (char* command, char** arguments, char** pathOutput)
{
	char* subString;
	unsigned counter = 0;
	unsigned flagOutput = 0;
	subString = strtok(command, DELIMITER);
	while (subString != NULL)
	{
		if (strcmp(subString, ">") == 0)
			flagOutput = 1;
		else
		{
			/*Se tiver a flag, a string vai receber o resultado do parser atual da strtok*/
			if (flagOutput){
				/*Mudando o valor da variavel pathOutput e atribuindo o valor na posicao de memoria da subString*/
				*pathOutput = subString;
			}
			else
			{
				arguments[counter] = (char*)malloc((strlen(subString) + 1)*sizeof(char*));
				if (arguments[counter] != NULL)
					strcpy(arguments[counter],subString);
				else
					return -1;
				counter++;
			}
		}
		subString = strtok(NULL,DELIMITER);
	}
	/*NULL é adicionado no final para que a chamada ao exec funcione*/
	arguments[counter + 1] = NULL;
	if (!flagOutput)
		*pathOutput = "";
	return 0;
}

/*Funcao que irá liberar o espaço de memória utilizado com o malloc
do array que armazena os argumentos que são passados para a execv*/
void freeArray(char** arguments)
{
	unsigned i = 0;
	while (arguments[i] != NULL)
	{
		free(arguments[i]);
		/*Para marcar os ponteiros que foram liberados da memoria, atribuimos NULL ao mesmo*/
		arguments[i] = NULL;
		i++;
	}
}

void printUserGuide ()
{
  printf(MAGENTA_COLOR);
  printf("1. Comandos válidos são aqueles que estão na /bin ou 'exit' ou 'man fabits'. ou 'clear'\n");
  printf("2. Tratamentos de erro foram feitos para os casos acima,\n   assim como para argumentos vazios ou apenas um char.\n");
  printf("3. Para alterar o caminho de saída, basta digitar o comando e argumentos opcionais,\n   seguido de '> caminhoArquivo/nomeArquivo'\n");
  printf("4. Se especificado apenas o nome do arquivo, então será salvo no diretório atual\n");
  printf("5. O comando cd funciona com a limitação de nomes de diretórios que não tenham espaço,\n   por conta da lógica de parseamento de string\n");
  printf("6. O uso do signal SIGUSR1 é feito através de outra linha de comando e, quando executado,\n   encerra o processo filho que está executando\n");
  printf("Por fim, os arquivos encontram-se no GitHub, através do seguinte link: github.com/FabianaFerreira/Sistemas-Operacionais\n");
  printf(RESET_COLOR);
}

void printUserGreeting ()
{
  printf(CYAN_COLOR);
  printf("\n/******************************************************************************/\n");
  printf("/*------ FABITS SHELL: UM SHELL SIMPLIFICADO PARA SISTEMAS OPERACIONAIS ------*/\n");
  printf("/******************************************************************************/\n");
  printf(RESET_COLOR);
  printf("\n");
  printf("\n");
  printf(MAGENTA_COLOR);
  printf("Para maiores informações sobre como utilizá-lo, digite 'man fabits'\n");
  printf(RESET_COLOR);
  printf("\n");
  printf("\n");
}
