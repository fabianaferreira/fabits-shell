/*Universidade Federal do Rio de Janeiro
  Departamento de Engenharia Eletrôncia e de Computação
  Sistemas Operacionais - 2018.2
  Aluna: Fabiana Ferreira Fonseca
  DRE: 115037241*/

/*TRABALHO: IMPLEMENTAÇÃO DE UM SHELL PARA LINUX COM MULTIPLAS TELAS*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "screen.h"
#include "functions.h"
#include "consts.h"


using namespace std;

/*Variavel global que armazena o pid do processo que eu criei com o meu shell*/
pid_t child_pid;
pid_t currentScreen_pid;
vector <Screen*> activeScreens;
Screen * currentScreen;

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

int main ()
{
	FILE* stream;
	char commandList[BUFFER*20];
	char userInput [BUFFER];
	char inputCopy [BUFFER];
	int p, f;
  	int rw_setup[2];
  	char message[BUFFER];
  	p = pipe(rw_setup);

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

	/*Comeca o programa que eh visto pelo usuario*/
	printUserGreeting();

	/*Loop enquanto nao sai do programa principal*/
	while (!exit)
	{
		printf(GREEN_COLOR);
		cout << "$fabitsShell: ";
		// cout << "Pid atual 1 : " << getpid() << endl;

		printf(RESET_COLOR);
		signal(SIGUSR1, signal_handler);
		if (fgets(userInput, BUFFER, stdin) != NULL)
		{
			/*Tratando a retirada do caracter de retorno que vem com a chamada da fgets*/
			unsigned inputLength = strlen(userInput);
			int flagCd = -1;
			int flagMan = -1;
			int flagClear = -1;
			int flagScreen = -1;
			int flagExit = -1;

			/*String auxiliar para pegar apenas o nome do comando e nao as suas opcoes
			na hora de checar sua existencia*/
			strcpy(inputCopy,userInput);
			strtok(inputCopy, DELIMITER);
			flagCd = strcmp(inputCopy, "cd");
			flagMan = strcmp(userInput, MAN_COMMAND);
			flagClear = strcmp(userInput, CLEAR_COMMAND);
			flagScreen = strcmp(userInput, SCREEN_COMMAND);
			flagExit = strcmp(userInput, EXIT_COMMAND);

			/*Tratando o caso em que o usuário apenas dá enter e quando o comando não existe*/
			if ((inputLength == 1 && userInput[inputLength - 1] == '\n') || inputLength == 2)
			{
				typeCommand();
				continue;
			}
			/*Testa todos os casos de comandos validos, se nao for, eh invalido e pede entrada de novo*/
			if (strstr(commandList, inputCopy) == NULL && flagExit != 0 && flagMan != 0 && flagCd != 0 && flagClear != 0 && flagScreen != 0)
			{
				printInvalidCommand();
				continue;
			}

			/*Se nao caiu nos ifs acima, o comando eh valido. Existe na pasta /bin ou eh exit ou eh man ou eh screen*/

			/*Se nao caiu em nenhum dos casos anteriores, pega o input e tira o \n*/
			if (inputLength > 1 && userInput[inputLength - 1] == '\n')
				userInput[inputLength - 1] = '\0';

			/*Trata e faz o parser da string recebida na linha de comando caso não seja man nem clear nem screen*/
			if (flagMan != 0 && flagClear != 0 && flagScreen != 0 && flagExit != 0)
				getArgumentsFromCommand(userInput,arguments, &pathOutput);


			/*Entrou com um comando que não é o exit*/
			if (flagExit == 0)
			{
				/*No caso do exit, preciso que o sigterm passe para o pid certo, o cara ativo no momento */
				/*Vai ter uma lista de array, preciso matar todos os filhos tambem*/

				exitAllScreens(activeScreens);
				exit = 1;
				printf("Saindo do shell. Obrigada por testar!\n");
			}
			else if (flagCd == 0)
				chdir(arguments[1]);

			else if (flagMan == 0)
				printUserGuide();

			else if (flagClear == 0)
				system("clear");

			else if (flagScreen == 0)
			{
				currentScreen = new Screen(true);	
		  		guard(mkfifo(currentScreen->getFilename().c_str(), 0777), "Could not create pipe");
				currentScreen_pid = fork();
				deactivateScreens(&activeScreens);	

				for (int i = 0; i < activeScreens.size(); i++) 
				{					
					if (activeScreens[i]->getStatus() == false)
						cout << "false" << endl;
					else
						cout << "true" << endl;
					cout << activeScreens[i]->getFilename()<< endl;
				}

				activeScreens.push_back(currentScreen);

				if (currentScreen_pid > 0)
				{
					//Eh o pai
					currentScreen->setPid(currentScreen_pid);

				}
				else if (currentScreen_pid == 0)
				{
					/*Eh o filho*/
					/*Vai ficar lendo de um arquivo, a procura de alguma alteracao*/
					// ifstream childScreenFile (currentScreen->getFilename());					
					// string line;
					// if (childScreenFile.is_open()) 
					// {
					// 	while (getline(childScreenFile, line)) 
					// 	{
					// 		cout << line << endl;
					// 	}
					// }

					// Child
				    int pipe_read_fd = guard(open(currentScreen->getFilename().c_str(), O_RDONLY), "Could not open pipe for reading");
				    char buf[20];
				    for (;;) {
				      ssize_t num_read = guard(read(pipe_read_fd, buf, sizeof(buf)), "Could not read from pipe");
				      if (num_read == 0) {
				        write_str(1, "Read EOF; closing read end\n");
				        // guard(close(pipe_read_fd), "Could not close pipe read end");
				        break;
				      } else {
				        write_str(1, "Read from pipe: ");
				        write_all(1, buf, num_read);
				        write_str(1, "\n");
				      }
				    }
				}
			}
			else
			{
				/*Tratamento do caminho para o comando a ser executado*/
				char* commandPath = (char*)malloc(sizeof(char*)*20);
				strcpy(commandPath, PATH);
				strcat(commandPath,arguments[0]);
				if (activeScreens.size() != 0)
				{
					/*Se for o caso de ter pelo menos uma screen ativa*/

					/*Pega a screen ativa atual*/
					Screen activeScreen = getActiveScreen(activeScreens);

					/*Debug para listar screens*/
					listScreens(activeScreens);					

					/*Debug para o nome do arquivo*/
					cout << activeScreen.getFilename() << endl;					

					/*Aqui eu preciso criar um arquivo e escrever nele o comando que a 
					screen tem que executar*/
					// activeScreen.createScreenFilename();
					// ofstream screenFile;								
					// screenFile.open(activeScreen.getFilename());
					// screenFile << commandPath;
					// screenFile.close();					

					// Parent
				    int pipe_write_fd = guard(open(activeScreen.getFilename().c_str(), O_WRONLY), "Could not open pipe for writing");
				    write_str(pipe_write_fd, commandPath);
				    guard(close(pipe_write_fd), "Could not close pipe write end");
				}
				else
				{
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
						waitpid(child_pid, NULL, WCONTINUED);
					}
					free(commandPath);
				}
			}

		/*Libera o espaço de memoria utilizado pelas strings dentro do array*/
		freeArray(arguments);
		}
	}
	/*Liberado o espaço de memoria alocado pelo proprio array*/
	free(arguments);
	delete currentScreen;
	return 0;
}
