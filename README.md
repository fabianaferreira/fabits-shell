# Fabits Shell
Repositório destinado à um projeto da disciplina de Sistemas Operacionais, do Departamento de Eletrônica da UFRJ

## Parte 1: Implementação de um shell
Prova de conceito para colocar em prática os conhecimentos adquiridos em sala de aula, referentes à chamadas de sistema e sinais. O trabalho foi desenvolvimento em C Ansi, utilizando conceitos gerais de manipulação de strings.

Apesar de não ser pedido, tratamentos de erros para comandos inválidos digitados foi feita, assim como a implementação do comando `cd`, que é um *built-in command* e também o `clear`.

Por fim, um man foi implementado, de forma a ter maiores informações de como o *shell* funciona. Para lê-lo, basta digitar o comando `man fabits`.

## Parte 2: Implementação de múltiplas telas no shell
As telas têm opções no comando, para diversas funções. Em geral, é possível listar as telas existentes, excluir alguma em específico ou trocar a que está ativa no momento. Para isso, são utilizadas diferentes opções adicionais ao comando.

Além disso, a implementação das diferentes telas se faz a partir de _fifos_ que são criadas dentro da pasta oculta `.files`, de forma que cada uma tenha a sua fila, que é responsável por receber os comandos processados pelo processo pai, a fim de ser executado na tela ativa no momento.

* Listar telas ativas: `screen -l`
* Excluir uma tela específica: `screen -rm <nome tela>`
* Alterar tela ativa: `screen -a <nome tela a ser ativada>`

## Extra: Desenvolvimento de um monitorador de tarefas básico
