#include "Cod.h"
#include "MinHeap.h"
#include "Huff.h"
#define ARQUIVO "paralelepipedo.txt"

int main(){

    unsigned int frequencia[MAX_NOS] = {0};

    preencher_tabela(frequencia, ARQUIVO);
    imprimir_tabela(frequencia);

    TNo* arvore = construir_arvore(frequencia);
    int** dicionario = create_dicionario(arvore);

    for (int i = 0; i < MAX_NOS; i++) {
        if(frequencia[i] > 0){
            printf("Letra '%c': ", i);
        
        
        int j = 0;
        while (dicionario[i][j] != -1) {
            printf("%d", dicionario[i][j]);
            j++;
        }
        printf("\n");

        }
    }

    return 0;
}
