#include "Cod.h"
#include "Huff.h"
#include "MinHeap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_NOS 256

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

void Codificar(char entrada[], char saida[]){


    FILE *entrada_arquivo = fopen(entrada, "rb");
    FILE *saida_arquivo = fopen(saida, "wb");

    unsigned int frequencia[MAX_NOS] = {0};

    preencher_tabela(frequencia, entrada);
    imprimir_tabela(frequencia);

    TNo* arvore = construir_arvore(frequencia);
    int** dicionario = create_dicionario(arvore);

    unsigned int contagem = 0;
    unsigned int bits_totais = 0;
    unsigned int bits_lixo = 0;
    unsigned char byte_buffer = 0;
    int contador_bits = 0;         
    int c;

    for (int i = 0; i < MAX_NOS; i++) {
        if(frequencia[i] > 0){
            contagem++;

            int j = 0;
            while (dicionario[i][j] != -1) {
                printf("%d", dicionario[i][j]);
                bits_totais += frequencia[i];
                j++;
            }
        }
    }

     if(bits_totais % 8 == 0){
        bits_lixo = 0;
    }else{
        bits_lixo = 8 - (bits_totais%8);
    }

    fwrite(&contagem, sizeof(int), 1, saida_arquivo);
    for(int i = 0; i < MAX_NOS; i++){
        if(frequencia[i] > 0){
            unsigned char caractere = (unsigned char)i;
            fwrite(&caractere, sizeof(unsigned char), 1, saida_arquivo);
            fwrite(&frequencia[i], sizeof(unsigned int), 1, saida_arquivo);
        }
    }
    fwrite(&bits_lixo, sizeof(unsigned char), 1, saida_arquivo);

    while ((c = fgetc(entrada_arquivo)) != EOF) {
        
        int j = 0;
        while (dicionario[c][j] != -1) {
            int bit = dicionario[c][j];

            byte_buffer = (byte_buffer << 1) | bit;
            contador_bits++;

            if (contador_bits == 8) {
                fwrite(&byte_buffer, sizeof(unsigned char), 1, saida_arquivo);
                byte_buffer = 0;    
                contador_bits = 0;   
            }
            j++;
        }
    }

    if (contador_bits > 0) {
        byte_buffer = byte_buffer << bits_lixo;
        fwrite(&byte_buffer, sizeof(unsigned char), 1, saida_arquivo);
    }
    

    fclose(entrada_arquivo);
    fclose(saida_arquivo);
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