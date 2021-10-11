# Fabits Shell
Repositório destinado à um projeto da disciplina de Sistemas Operacionais, do Departamento de Eletrônica da UFRJ

## Parte 1: Implementação de um shell
Prova de conceito para colocar em prática os conhecimentos adquiridos em sala de aula, referentes à chamadas de sistema e sinais. O trabalho foi desenvolvido em C+, utilizando conceitos gerais de manipulação de strings.

Tratamentos de erros para comandos inválidos digitados foi feita, assim como a implementação do comando `cd`, que é um *built-in command* e também o `clear`.

Por fim, um man foi implementado, de forma a ter maiores informações de como o *shell* funciona. Para lê-lo, basta digitar o comando `man fabits`.

## Parte 2: Implementação de múltiplas telas no shell
As telas têm opções no comando, para diversas funções. Em geral, é possível listar as telas existentes, excluir alguma em específico ou trocar a que está ativa no momento. Para isso, são utilizadas diferentes opções adicionais ao comando.

Além disso, a implementação das diferentes telas se faz a partir de _fifos_ que são criadas dentro da pasta oculta `.files`, de forma que cada uma tenha a sua fila, que é responsável por receber os comandos processados pelo processo pai, a fim de ser executado na tela ativa no momento.

* Listar telas ativas: `screen list`
* Excluir uma tela específica: `screen remove <nome tela>`
* Alterar tela ativa: `screen switch <nome tela a ser ativada>`

Referências utilizadas para funções da FIFO: https://jameshfisher.com/2017/02/21/mkfifo-c.html

## Extra: Desenvolvimento de um monitorador de tarefas básico
Para essa implementação, utilizou-se a leitura de arquivos de sistema que contém as informações de uso de CPU e de RAM. Há uma _thread_ rodando no programa principal que faz esse _loop_, de forma que seja possível ler a interrupção através de uma tela, pelo usuário. Isso é necessário, pois a leitura através da `getchar()` é síncrona.

Referências: https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
