/*Universidade Federal do Rio de Janeiro
  Departamento de Engenharia Eletrôncia e de Computação
  Sistemas Operacionais - 2018.2
  Aluna: Fabiana Ferreira Fonseca
  DRE: 115037241*/

/*TRABALHO: IMPLEMENTAÇÃO DE UM SHELL PARA LINUX COM MULTIPLAS TELAS*/

#define EOS				"\0"
#define BUFFER			100
#define DELIMITER 		" "
#define CLEAR_COMMAND 	"clear\n"
#define SCREEN_COMMAND 	"screen\n"
#define EXIT_COMMAND 	"exit\n"
#define MAN_COMMAND		"man fabits\n"
#define PATH 			"/bin/"
#define CYAN_COLOR		"\033[1;36m"
#define GREEN_COLOR		"\033[1;32m"
#define RED_COLOR		"\033[1;31m"
#define MAGENTA_COLOR	"\033[1;35m"
#define RESET_COLOR 	"\033[0m"
#define FIFO_PATH		"./files/"