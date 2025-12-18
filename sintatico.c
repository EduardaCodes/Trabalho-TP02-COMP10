#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

extern void inicializarLexico(FILE *arq);
extern Token proximoToken();

static Token tokenAtual;
static int erros = 0;

void erroSintatico(const char *mensagem) {
    printf("ERRO SINTATICO [Linha %d, Coluna %d]: %s\n", 
           tokenAtual.linha, tokenAtual.coluna, mensagem);
    printf("Token encontrado: %s\n", tokenAtual.lexema);
    erros++;
}

void casaToken(TipoToken esperado) {
    if (tokenAtual.tipo == esperado) {
        printf("Token aceito: %s\n", tokenAtual.lexema);
        tokenAtual = proximoToken();
    } else {
        char msg[256];
        sprintf(msg, "Token esperado diferente do encontrado");
        erroSintatico(msg);
        tokenAtual = proximoToken();
    }
}

void fator();
void termo();
void expressaoSimples();
void expressao();
void comando();

void listaIdentificadores() {
    casaToken(TOKEN_IDENTIFICADOR);
    while (tokenAtual.tipo == TOKEN_VIRGULA) {
        casaToken(TOKEN_VIRGULA);
        casaToken(TOKEN_IDENTIFICADOR);
    }
}

void tipo() {
    if (tokenAtual.tipo == TOKEN_INTEGER) {
        casaToken(TOKEN_INTEGER);
    } else if (tokenAtual.tipo == TOKEN_BOOLEAN) {
        casaToken(TOKEN_BOOLEAN);
    } else {
        erroSintatico("Tipo esperado (integer ou boolean)");
    }
}

void declaracaoVariaveis() {
    listaIdentificadores();
    casaToken(TOKEN_DOIS_PONTOS);
    tipo();
    casaToken(TOKEN_PONTO_VIRGULA);
}

void parteDeclaracoesVariaveis() {
    if (tokenAtual.tipo == TOKEN_VAR) {
        casaToken(TOKEN_VAR);
        declaracaoVariaveis();
        while (tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
            declaracaoVariaveis();
        }
    }
}

void fator() {
    if (tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
        casaToken(TOKEN_IDENTIFICADOR);
    } else if (tokenAtual.tipo == TOKEN_NUMERO) {
        casaToken(TOKEN_NUMERO);
    } else if (tokenAtual.tipo == TOKEN_TRUE) {
        casaToken(TOKEN_TRUE);
    } else if (tokenAtual.tipo == TOKEN_FALSE) {
        casaToken(TOKEN_FALSE);
    } else if (tokenAtual.tipo == TOKEN_ABRE_PAREN) {
        casaToken(TOKEN_ABRE_PAREN);
        expressao();
        casaToken(TOKEN_FECHA_PAREN);
    } else if (tokenAtual.tipo == TOKEN_NOT) {
        casaToken(TOKEN_NOT);
        fator();
    } else {
        erroSintatico("Fator esperado (identificador, numero, true, false, expressao entre parenteses ou not)");
    }
}

void termo() {
    fator();
    while (tokenAtual.tipo == TOKEN_MULTIPLICACAO || 
           tokenAtual.tipo == TOKEN_DIVISAO ||
           tokenAtual.tipo == TOKEN_AND) {
        if (tokenAtual.tipo == TOKEN_MULTIPLICACAO) {
            casaToken(TOKEN_MULTIPLICACAO);
        } else if (tokenAtual.tipo == TOKEN_DIVISAO) {
            casaToken(TOKEN_DIVISAO);
        } else {
            casaToken(TOKEN_AND);
        }
        fator();
    }
}

void expressaoSimples() {
    if (tokenAtual.tipo == TOKEN_MAIS || tokenAtual.tipo == TOKEN_MENOS) {
        if (tokenAtual.tipo == TOKEN_MAIS) {
            casaToken(TOKEN_MAIS);
        } else {
            casaToken(TOKEN_MENOS);
        }
    }
    termo();
    while (tokenAtual.tipo == TOKEN_MAIS || 
           tokenAtual.tipo == TOKEN_MENOS ||
           tokenAtual.tipo == TOKEN_OR) {
        if (tokenAtual.tipo == TOKEN_MAIS) {
            casaToken(TOKEN_MAIS);
        } else if (tokenAtual.tipo == TOKEN_MENOS) {
            casaToken(TOKEN_MENOS);
        } else {
            casaToken(TOKEN_OR);
        }
        termo();
    }
}

void expressao() {
    expressaoSimples();
    if (tokenAtual.tipo == TOKEN_IGUAL ||
        tokenAtual.tipo == TOKEN_DIFERENTE ||
        tokenAtual.tipo == TOKEN_MENOR ||
        tokenAtual.tipo == TOKEN_MENOR_IGUAL ||
        tokenAtual.tipo == TOKEN_MAIOR ||
        tokenAtual.tipo == TOKEN_MAIOR_IGUAL) {
        TipoToken operador = tokenAtual.tipo;
        switch (operador) {
            case TOKEN_IGUAL: casaToken(TOKEN_IGUAL); break;
            case TOKEN_DIFERENTE: casaToken(TOKEN_DIFERENTE); break;
            case TOKEN_MENOR: casaToken(TOKEN_MENOR); break;
            case TOKEN_MENOR_IGUAL: casaToken(TOKEN_MENOR_IGUAL); break;
            case TOKEN_MAIOR: casaToken(TOKEN_MAIOR); break;
            case TOKEN_MAIOR_IGUAL: casaToken(TOKEN_MAIOR_IGUAL); break;
            default: break;
        }
        expressaoSimples();
    }
}

void atribuicao() {
    casaToken(TOKEN_IDENTIFICADOR);
    casaToken(TOKEN_ATRIBUICAO);
    expressao();
}

void comandoCondicional() {
    casaToken(TOKEN_IF);
    expressao();
    casaToken(TOKEN_THEN);
    comando();
    if (tokenAtual.tipo == TOKEN_ELSE) {
        casaToken(TOKEN_ELSE);
        comando();
    }
}

void comandoRepetitivo() {
    casaToken(TOKEN_WHILE);
    expressao();
    casaToken(TOKEN_DO);
    comando();
}

void comandoEntrada() {
    casaToken(TOKEN_READ);
    casaToken(TOKEN_ABRE_PAREN);
    listaIdentificadores();
    casaToken(TOKEN_FECHA_PAREN);
}

void comandoSaida() {
    casaToken(TOKEN_WRITE);
    casaToken(TOKEN_ABRE_PAREN);
    listaIdentificadores();
    casaToken(TOKEN_FECHA_PAREN);
}

// CORREÇÃO DEFINITIVA APLICADA
void comandoComposto() {
    casaToken(TOKEN_BEGIN);

    while (tokenAtual.tipo != TOKEN_END) {
        comando();
        if (tokenAtual.tipo == TOKEN_PONTO_VIRGULA) {
            casaToken(TOKEN_PONTO_VIRGULA);
        } else {
            break;
        }
    }

    casaToken(TOKEN_END);
}

void comando() {
    if (tokenAtual.tipo == TOKEN_END ||
        tokenAtual.tipo == TOKEN_ELSE ||
        tokenAtual.tipo == TOKEN_PONTO) {
        return;
    }

    if (tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
        atribuicao();
    } else if (tokenAtual.tipo == TOKEN_BEGIN) {
        comandoComposto();
    } else if (tokenAtual.tipo == TOKEN_IF) {
        comandoCondicional();
    } else if (tokenAtual.tipo == TOKEN_WHILE) {
        comandoRepetitivo();
    } else if (tokenAtual.tipo == TOKEN_READ) {
        comandoEntrada();
    } else if (tokenAtual.tipo == TOKEN_WRITE) {
        comandoSaida();
    } else {
        erroSintatico("Comando esperado");
        tokenAtual = proximoToken();
    }
}

void bloco() {
    parteDeclaracoesVariaveis();
    comandoComposto();
}

void programa() {
    casaToken(TOKEN_PROGRAM);
    casaToken(TOKEN_IDENTIFICADOR);
    casaToken(TOKEN_PONTO_VIRGULA);
    bloco();
    casaToken(TOKEN_PONTO);
}

int analisarSintatico(FILE *arquivo) {
    inicializarLexico(arquivo);
    tokenAtual = proximoToken();

    printf("=== INICIANDO ANALISE SINTATICA ===\n\n");
    programa();

    if (tokenAtual.tipo == TOKEN_EOF && erros == 0) {
        printf("\n=== ANALISE SINTATICA CONCLUIDA COM SUCESSO ===\n");
        return 1;
    } else {
        printf("\n=== ANALISE SINTATICA CONCLUIDA COM %d ERRO(S) ===\n", erros);
        return 0;
    }
}   