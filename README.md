# 🔎 Analisador Sintático em C — MicroPascal

## 📌 Descrição
Este projeto implementa um **Analisador Sintático**, em linguagem **C**, para a linguagem **MicroPascal**.  
O analisador consome os tokens gerados pelo analisador léxico (TP01) e valida a estrutura sintática completa do programa, conforme a gramática definida para a linguagem.

O programa é capaz de:
- Reconhecer a estrutura sintática de programas MicroPascal
- Validar comandos, declarações e expressões
- Detectar e relatar **erros sintáticos**, informando lexema, linha e coluna
- Processar arquivos fonte utilizados como casos de teste

Este trabalho corresponde ao **TP02** da disciplina **Linguagens Formais, Autômatos e Compiladores (COMP10)**.

---

## ⚙️ Como compilar

### 🔹 Linux / WSL
```bash
make
````

### 🔹 Compilação manual

```bash
gcc main.c lexico.c sintatico.c -o analisador
```

---

## ▶️ Como executar

O analisador recebe como entrada um arquivo contendo um programa para análise:

```bash
./analisador testeCerto1.c
```

No Windows:

```bash
analisador.exe testeCerto1.c
```

---

## 📂 Saídas

* **Terminal** → Mensagens de sucesso ou erro sintático
* Em caso de erro, são exibidos:

  * tipo do erro
  * lexema encontrado
  * linha e coluna no código-fonte

---

## 🧪 Testes incluídos

O projeto possui **6 programas de teste**, divididos em corretos e incorretos.

### ✅ Programas corretos

* `testeCerto1.c` — Atribuição simples
* `testeCerto2.c` — Estrutura condicional `if/else`
* `testeCerto3.c` — Estrutura de repetição `while`

### ❌ Programas com erro

* `erro1.c` — Falta de ponto e vírgula
* `erro2.c` — Comando `if` sem `then`
* `erro3.c` — Finalização incorreta do programa (`end.` ausente)

---

## 📑 Relatório

O arquivo **TP02-COMP10.pdf** contém:

* Introdução
* Implementação

  * Estruturas (`struct` e `enum`)
  * Funções do analisador sintático
  * Discussão sobre o uso de AFD
* Testes (3 corretos e 3 com erro)
* Conclusão
* Referências
* Anexos (arquivos fonte)

---

## 📂 Estrutura do projeto

```text
.
├── Makefile
├── main.c
├── lexico.c
├── sintatico.c
├── tokens.h
├── testeCerto1.c
├── testeCerto2.c
├── testeCerto3.c
├── erro1.c
├── erro2.c
├── erro3.c
├── analisador.exe
├── TP02-COMP10.pdf
└── README.md
```

---

## 👨‍💻 Autores

**Alunos(as):**

* Ana Beatriz Alves
* Artur Coelho
* David Cordeiro
* Eduarda Alves
* Guilherme Andrade

**Professor:** Marcelo Eustáquio
**Disciplina:** Linguagens Formais, Autômatos e Compiladores — COMP10

```
