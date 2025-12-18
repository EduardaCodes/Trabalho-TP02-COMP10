ANALISADOR SINTATICO PARA MICROPASCAL
=====================================

DESCRICAO:
----------
Analisador sintatico descendente recursivo para a linguagem MicroPascal.
Implementa as partes 1, 2, 3 e 4 do projeto de compiladores.

ARQUIVOS:
---------
- tokens.h      : Definicoes de todos os tokens
- lexico.c      : Analisador lexico
- sintatico.c   : Analisador sintatico
- main.c        : Programa principal
- Makefile      : Arquivo de compilacao

COMPILACAO:
-----------
Opcao 1 (usando Make):
  make

Opcao 2 (manual):
  gcc -o compilador main.c lexico.c sintatico.c

EXECUCAO:
---------
  ./compilador <arquivo.pas>

Exemplo:
  ./compilador programa.pas

ESTRUTURA DO MICROPASCAL:
-------------------------
program NomePrograma;
var
  x, y : integer;
  resultado : boolean;
begin
  read(x, y);
  resultado := x > y;
  if resultado then
    write(x)
  else
    write(y)
end.

FEATURES IMPLEMENTADAS:
-----------------------
- Declaracao de variaveis (integer, boolean)
- Comandos de atribuicao
- Estruturas condicionais (if-then-else)
- Estruturas de repeticao (while-do)
- Comandos de entrada/saida (read, write)
- Expressoes aritmeticas e logicas
- Operadores relacionais
- Precedencia de operadores

AUTOR:
------
Projeto de Compiladores - Analisador Sintatico MicroPascal