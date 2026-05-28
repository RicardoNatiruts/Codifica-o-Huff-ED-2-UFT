#include "Cod.h"
#include "MinHeap.h"
#include "Huff.h"
#define ARQUIVO "paralelepipedo.txt"

int main(){

    FILE *arquivo = fopen("codificado.huff", "wb");

    unsigned int frequencia[MAX_NOS] = {0};
    unsigned int contagem = 0;

    preencher_tabela(frequencia, ARQUIVO);
    imprimir_tabela(frequencia);

    TNo* arvore = construir_arvore(frequencia);
    int** dicionario = create_dicionario(arvore);

    for (int i = 0; i < MAX_NOS; i++) {
        if(frequencia[i] > 0){
            contagem++;
            printf("Letra '%c': ", i);
        
        
        int j = 0;
        while (dicionario[i][j] != -1) {
            printf("%d", dicionario[i][j]);
            j++;
        }
        printf("\n");

        }
    }

    fwrite(&contagem, sizeof(int), 1, arquivo);
    for(int i = 0; i < MAX_NOS; i++){
        if(frequencia[i] > 0){
            unsigned char caractere = (unsigned char)i;
            fwrite(&caractere, sizeof(char), 1, arquivo);
            fwrite(&frequencia[i], sizeof(int), 1, arquivo);
        }
    }
    fclose(arquivo);

    return 0;
}
