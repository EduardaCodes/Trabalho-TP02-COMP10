#include <stdio.h>
#include <stdlib.h>

extern int analisarSintatico(FILE *arquivo);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo.pas>\n", argv[0]);
        return 1;
    }
    
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo: %s\n", argv[1]);
        return 1;
    }
    
    printf("Analisando arquivo: %s\n\n", argv[1]);
    
    int sucesso = analisarSintatico(arquivo);
    
    fclose(arquivo);
    
    return sucesso ? 0 : 1;
}