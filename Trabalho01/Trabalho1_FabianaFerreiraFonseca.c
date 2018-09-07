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

#define EOS				"\0"
#define BUFFER			100
#define DELIMITER 		" "
#define EXIT_COMMAND 	"exit"
#define MAN_COMMAND		"man fabits\n"
#define PATH 			"/bin/"
#define CYAN_COLOR		"\033[1;36m"
#define GREEN_COLOR		"\033[1;32m"
#define RED_COLOR		"\033[1;31m"
#define MAGENTA_COLOR	"\033[1;35m"
#define RESET_COLOR 	"\033[0m"


/*Declaracao da funcao para Tratamento de strings*/
int getArgumentsFromCommand(char*, char**, char**);
void signal_handler(int);
void freeArray(char**);


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

/*Variavel global que armazena o pid do processo que eu criei com o meu shell*/
pid_t child_pid;

/*Funcao que funciona como listener do sinal SIGUSR1, que matará 
o processo que está rodando no meu shell*/
void signal_handler(int sigNumber) 
{
	if (sigNumber == SIGUSR1 && child_pid != getpid()) 
	{	
		printf("Recebi um sinal de SIGUSR1. Terminando processo criado.\n");
		kill(child_pid, SIGTERM);
	}
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

/*-------------------------------------------------MAIN--------------------------------------------------*/
int main () 
{	
	FILE* stream;
	char commandList[BUFFER*20];
	char userInput [BUFFER];
	char inputCopy [BUFFER];
	/*Alocando memoria para criar o array que armazenará os argumentos*/
	char** arguments = (char**)malloc(BUFFER*sizeof(char*));
	char* pathOutput = (char*)malloc(sizeof(char*));
	unsigned exit = 0;
	int pipefd[2];

	/*Faço uma chamada de execv para listar os comandos que estão na 
	pasta bin, de forma a conseguir tratar o erro, caso o usuário entre
	com um comando que não está na pasta*/
	pipe(pipefd);
	pid_t binDir_pid = fork();
	if (binDir_pid == 0)
	{
		//Fecha o lado de entrada do pipe (do filho)
		close(pipefd[0]);

		dup2(pipefd[1], fileno(stdout));
		close(pipefd[1]);

		execlp("/bin/dir", "dir","-1","/bin/",NULL);
	}
	else 
	{
		wait(NULL);
		close(pipefd[1]);
		while(read(pipefd[0], commandList, sizeof(commandList)) != 0) {}
	} 
	
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
			int flagCd = -1;
			int flagMan = -1;

			/*String auxiliar para pegar apenas o nome do comando e nao as suas opcoes
			na hora de checar sua existencia*/
			strcpy(inputCopy,userInput);
			strtok(inputCopy, DELIMITER);
			flagCd = strcmp(inputCopy, "cd");
			flagMan = strcmp(userInput, MAN_COMMAND);
			
			/*Tratando o caso em que o usuário apenas dá enter e quando o comando não existe*/
			if ((inputLength == 1 && userInput[inputLength - 1] == '\n') || inputLength == 2) 
			{	
				printf(RED_COLOR);
				printf("Digite um comando válido\n");
				printf(RESET_COLOR);
				continue;
			}
			if (strstr(commandList, inputCopy) == NULL && strstr(inputCopy,EXIT_COMMAND) == NULL && flagMan != 0 && flagCd != 0) 
			{				
				printf(RED_COLOR);
				printf("Comando não existente. Por favor, digite novamente.\n");
				printf(RESET_COLOR);
				continue;
			}
			

			/*------Digitou um comando que existe na pasta /bin ou é exit ou é man-----*/

			/*Se nao caiu em nenhum dos casos anteriores, pega o input e tira o \n*/		
			if (inputLength > 1 && userInput[inputLength - 1] == '\n') 
				userInput[inputLength - 1] = '\0';					
			
			/*Trata e faz o parser da string recebida na linha de comando caso não seja man nem exit*/
			if (flagCd != 0 && flagMan != 0)
				getArgumentsFromCommand(userInput,arguments, &pathOutput);
			
			/*Entrou com um comando que não é o exit*/
			if (strcmp(userInput,EXIT_COMMAND) != 0 && flagMan != 0 && flagCd != 0) 
			{
				/*Tratamento do caminho para o comando a ser executado*/
				char* commandPath = (char*)malloc(sizeof(char*)*20);
				strcpy(commandPath, PATH);
				strcat(commandPath,arguments[0]);
				child_pid = fork();
				if (child_pid == 0) 
				{
				/*CHILD*/
					/*Testa o caso em que o usuario não quer printar na tela a saída do comando
					  Nesse caso, o usuario coloca no comando onde que ele quer salvar a saida*/
					if (strlen(pathOutput) != 0) 
					{
						printf("Caminho da saida foi configurado para %s\n", pathOutput);
						stream = fopen(pathOutput, "w");
						dup2(fileno(stream), fileno(stdout));
					}
					/*Executa o comando pedido pelo usuario*/
					execv(commandPath, arguments);
	
					if (strlen(pathOutput) != 0)
						fclose(stream);
				}
				else 
				{
					/*PARENT*/
					/*Usei o WCONTINUED pois se fosse NULL, estava recebendo um warning de cast de pointer para int.
					  A descrição da constante: "also return if a stopped child has been resumed by delivery of SIGCONT*/
					waitpid(child_pid,NULL, WCONTINUED);						
				}					
			free(commandPath);			
			}
			else if (flagCd == 0) 
			{
				chdir(arguments[1]);
			}
			else if (flagMan == 0) 
			{
				printf(MAGENTA_COLOR);
				printf("1. Comandos válidos são aqueles que estão na /bin ou 'exit' ou 'man fabits'.\n");
				printf("2. Tratamentos de erro foram feitos para os casos acima,\n   assim como para argumentos vazios ou apenas um char.\n");
				printf("3. Para alterar o caminho de saída, basta digitar o comando e argumentos opcionais,\n   seguido de '> caminhoArquivo/nomeArquivo'\n");
				printf("4. Se especificado apenas o nome do arquivo, então será salvo no diretório atual\n");
				printf("5. O comando cd funciona com a limitação de nomes de diretórios que não tenham espaço,\n   por conta da lógica de parseamento de string\n");
				printf("6. O uso do signal SIGUSR1 é feito através de outra linha de comando e, quando executado,\n   encerra o processo filho que está executando\n");
				printf(RESET_COLOR);
			}
			else 
			{
				exit = 1;					
				printf("Saindo do shell. Obrigada por testar!\n");
			}			
		}
		/*Libera o espaço de memoria utilizado pelas strings dentro do array*/
		freeArray(arguments);
	}
	/*Liberado o espaço de memoria alocado pelo proprio array*/	
	free(arguments);
	return 0;
}
