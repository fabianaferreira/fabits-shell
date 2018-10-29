/*Universidade Federal do Rio de Janeiro
  Departamento de Engenharia Eletrôncia e de Computação
  Sistemas Operacionas - 2018.2
  Aluna: Fabiana Ferreira Fonseca
  DRE: 115037241*/

/*TRABALHO: IMPLEMENTAÇÃO DE UM SHELL PARA LINUX COM MULTIPLAS TELAS*/

/*Declaracao da funcao para Tratamento de strings*/
int getArgumentsFromCommand(char*, char**, char**);

void freeArray(char**);

void printUserGuide ();

void printUserGreeting ();

void typeCommand ();

void printInvalidCommand ();
