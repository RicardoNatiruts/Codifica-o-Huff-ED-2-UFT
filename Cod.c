#include "Cod.h"

void preencher_tabela(unsigned int frequencia[], char exemplo[]){
    FILE *arquivo = fopen(exemplo, "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int byte;
    while ((byte = fgetc(arquivo)) != EOF) {
        frequencia[byte]++;
    }
    fclose(arquivo);
}

void imprimir_tabela(unsigned int frequencia[]){
    for(int i = 0; i < 256; i++){
        if(frequencia[i] > 0)
            printf("%c: %d\n", i, frequencia[i]);
    }
}

/*
int main(){

    FILE *arquivo = fopen("bits.huff", "wb");

    int meus_bits[8] = {1, 0, 1, 1, 0, 0, 1, 1};
    unsigned char byte = 0;

    for(int i = 0; i < 8; i++){
        byte = (byte << 1) | meus_bits[i];
    }
    
    fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    fclose(arquivo);


    return 0;
}


#include "min_huff.c"


#define TAMANHO_TABELA 256

int main() {
    unsigned int frequencia[TAMANHO_TABELA] = {0}; 
    
    FILE *arquivo = fopen("teste.txt", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int byte;
    unsigned int total_bytes = 0;

    while ((byte = fgetc(arquivo)) != EOF) {
        frequencia[byte]++;
        total_bytes++;
    }
    fclose(arquivo);

    MinHeap *heap = criar_min_heap(256);

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        if (frequencia[i] > 0) {
            HuffNode *novo_no = criar_no(i, frequencia[i]);
            insert_min_heap(heap, novo_no);
        }
    }

    return 0;
}

*/