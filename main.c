#include "Cod.h"
#include "MinHeap.h"
#include "Huff.h"
#include "Decod.h"
#include <string.h>
#include <stdio.h>

#define ARQUIVO "casmurro.txt"

int main(int argc, char *argv[]){

    if(argc != 4){
        printf("Erro na execução do Programa, (Estrutura =>\n\pPROGRMA / OPERAÇÃO (-c||-d) / ARQUIVO ENTRADA / ARQUIVO SAIDA\n);");
        return 1;
    }

    if(strcmp(argv[1], "-c") == 0){
        Codificar(argv[2], argv[3]);
        printf("Arquivo compactado");
    }
    else if(strcmp(argv[1], "-d") == 0){
        Decodificar(argv[2], argv[3]);
        printf("Arquivo decompactado");
    }
    else{
        printf("Erro: Flag '%s' desconhecida.\n", argv[1]);
        printf("Por favor, use '-c' para compactar ou '-d' para descompactar.\n");
        return 1;
    }
    return 0;
}
