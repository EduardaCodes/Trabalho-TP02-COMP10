#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"

static FILE *arquivo;
static int linha = 1;
static int coluna = 0;
static char caractereAtual;

typedef struct {
    char *palavra;
    TipoToken token;
} PalavraReservada;

static PalavraReservada palavrasReservadas[] = {
    {"program", TOKEN_PROGRAM},
    {"var", TOKEN_VAR},
    {"begin", TOKEN_BEGIN},
    {"end", TOKEN_END},
    {"if", TOKEN_IF},
    {"then", TOKEN_THEN},
    {"else", TOKEN_ELSE},
    {"while", TOKEN_WHILE},
    {"do", TOKEN_DO},
    {"read", TOKEN_READ},
    {"write", TOKEN_WRITE},
    {"integer", TOKEN_INTEGER},
    {"boolean", TOKEN_BOOLEAN},
    {"and", TOKEN_AND},
    {"or", TOKEN_OR},
    {"not", TOKEN_NOT},
    {"true", TOKEN_TRUE},
    {"false", TOKEN_FALSE},
    {NULL, TOKEN_ERRO}
};

void inicializarLexico(FILE *arq) {
    arquivo = arq;
    linha = 1;
    coluna = 0;
    caractereAtual = fgetc(arquivo);
    if (caractereAtual != EOF) coluna = 1;
}

static void avancarCaractere() {
    if (caractereAtual == '\n') {
        linha++;
        coluna = 0;
    }
    caractereAtual = fgetc(arquivo);
    coluna++;
}

static void pularEspacos() {
    while (caractereAtual != EOF && isspace(caractereAtual)) {
        avancarCaractere();
    }
}

static void pularComentario() {
    if (caractereAtual == '{') {
        avancarCaractere();
        while (caractereAtual != EOF && caractereAtual != '}') {
            avancarCaractere();
        }
        if (caractereAtual == '}') {
            avancarCaractere();
        }
    }
}

static TipoToken buscarPalavraReservada(const char *lexema) {
    for (int i = 0; palavrasReservadas[i].palavra != NULL; i++) {
        if (strcmp(lexema, palavrasReservadas[i].palavra) == 0) {
            return palavrasReservadas[i].token;
        }
    }
    return TOKEN_IDENTIFICADOR;
}

Token proximoToken() {
    Token token;
    token.linha = linha;
    token.coluna = coluna;
    token.lexema[0] = '\0';
    
    pularEspacos();
    
    if (caractereAtual == '{') {
        pularComentario();
        return proximoToken();
    }
    
    if (caractereAtual == EOF) {
        token.tipo = TOKEN_EOF;
        strcpy(token.lexema, "EOF");
        return token;
    }
    
    if (isalpha(caractereAtual)) {
        int i = 0;
        while (isalnum(caractereAtual) || caractereAtual == '_') {
            token.lexema[i++] = tolower(caractereAtual);
            avancarCaractere();
        }
        token.lexema[i] = '\0';
        token.tipo = buscarPalavraReservada(token.lexema);
        return token;
    }
    
    if (isdigit(caractereAtual)) {
        int i = 0;
        while (isdigit(caractereAtual)) {
            token.lexema[i++] = caractereAtual;
            avancarCaractere();
        }
        token.lexema[i] = '\0';
        token.tipo = TOKEN_NUMERO;
        return token;
    }
    
    switch (caractereAtual) {
        case ':':
            token.lexema[0] = caractereAtual;
            avancarCaractere();
            if (caractereAtual == '=') {
                token.lexema[1] = caractereAtual;
                token.lexema[2] = '\0';
                token.tipo = TOKEN_ATRIBUICAO;
                avancarCaractere();
            } else {
                token.lexema[1] = '\0';
                token.tipo = TOKEN_DOIS_PONTOS;
            }
            break;
        case ';':
            token.tipo = TOKEN_PONTO_VIRGULA;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case ',':
            token.tipo = TOKEN_VIRGULA;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '.':
            token.tipo = TOKEN_PONTO;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '(':
            token.tipo = TOKEN_ABRE_PAREN;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case ')':
            token.tipo = TOKEN_FECHA_PAREN;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '+':
            token.tipo = TOKEN_MAIS;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '-':
            token.tipo = TOKEN_MENOS;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '*':
            token.tipo = TOKEN_MULTIPLICACAO;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '/':
            token.tipo = TOKEN_DIVISAO;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '=':
            token.tipo = TOKEN_IGUAL;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
        case '<':
            token.lexema[0] = caractereAtual;
            avancarCaractere();
            if (caractereAtual == '=') {
                token.lexema[1] = caractereAtual;
                token.lexema[2] = '\0';
                token.tipo = TOKEN_MENOR_IGUAL;
                avancarCaractere();
            } else if (caractereAtual == '>') {
                token.lexema[1] = caractereAtual;
                token.lexema[2] = '\0';
                token.tipo = TOKEN_DIFERENTE;
                avancarCaractere();
            } else {
                token.lexema[1] = '\0';
                token.tipo = TOKEN_MENOR;
            }
            break;
        case '>':
            token.lexema[0] = caractereAtual;
            avancarCaractere();
            if (caractereAtual == '=') {
                token.lexema[1] = caractereAtual;
                token.lexema[2] = '\0';
                token.tipo = TOKEN_MAIOR_IGUAL;
                avancarCaractere();
            } else {
                token.lexema[1] = '\0';
                token.tipo = TOKEN_MAIOR;
            }
            break;
        default:
            token.tipo = TOKEN_ERRO;
            token.lexema[0] = caractereAtual;
            token.lexema[1] = '\0';
            avancarCaractere();
            break;
    }
    
    return token;
}