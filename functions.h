/*Universidade Federal do Rio de Janeiro
   Departamento de Engenharia Eletrôncia e de Computação
   Sistemas Operacionais - 2018.2
   Aluna: Fabiana Ferreira Fonseca
   DRE: 115037241*/

/*TRABALHO: IMPLEMENTAÇÃO DE UM SHELL PARA LINUX COM MULTIPLAS TELAS*/

#include <vector>
#include <string>

/*Declaracao da funcao para Tratamento de strings*/
int getArgumentsFromCommand(char*, char**, std::string*);

void freeArray(char**);

void printUserGuide ();

void printUserGreeting ();

void typeCommand ();

void printInvalidCommand ();

std::string createScreenFilename(pid_t);

int checkError(int, std::string);

void writeAllToFifo(int fd, char * bytes, size_t nbyte);

void write_str(int, std::string);

std::vector<std::string> parseString (std::string, char);

double getCurrentUseOfCPU ();

int getCurrentUseOfRAM ();
