#include "Cod.h"
#include "Huff.h"
#include "MinHeap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TAM_FREQ 256

void extrair_payload(FILE* arquivo, FILE* saida, TNo* arvore_huff, unsigned char lixo){
    TNo* auxiliar = arvore_huff;
    unsigned char byte, next_byte;

    if (fread(&byte, sizeof(unsigned char), 1, arquivo) != 1) {
        return; 
    }

    while(fread(&next_byte, sizeof(unsigned char), 1, arquivo) == 1){
        for(int i = 7; i > -1; i--){
            int bit = (byte >> i) & 1;

            if(bit == 0){
                auxiliar = auxiliar->esq;
            }
            else{
                auxiliar = auxiliar->dir;
            }
            if(!auxiliar->dir && !auxiliar->esq){
                fwrite(&(auxiliar->byte), sizeof(unsigned char), 1, saida);
                auxiliar = arvore_huff;
            }
        }
        byte = next_byte;
    }

    for(int i = 7; i > lixo; i--){
        int bit = (byte >> i) & 1;

        if(bit == 0){
            auxiliar = auxiliar->esq;
        }
        else{
            auxiliar = auxiliar->dir;
        }
        if(!auxiliar->dir && !auxiliar->esq){
            fwrite(&(auxiliar->byte), sizeof(unsigned char), 1, saida);
            auxiliar = arvore_huff;
        }
    }

    return;
}

void Decodificar(char Huff[], char ArquivoSaida[]){
    int cont_bytes = 0;

    FILE *arquivo = fopen(Huff, "rb");
    FILE *saida = fopen(ArquivoSaida, "wb");

    fread(&cont_bytes, sizeof(int), 1, arquivo);

    int frequencia[TAM_FREQ] = {0};

    for (int i = 0; i < cont_bytes; i++){
        unsigned char caractere;
        int frequenciaChar;

        fread(&caractere, sizeof(unsigned char), 1, arquivo);
        fread(&frequenciaChar, sizeof(int), 1, arquivo);

        frequencia[caractere] = frequenciaChar;
    }

    TNo* arvore_huff = construir_arvore(frequencia);
    
    unsigned char lixo;
    fread(&lixo, sizeof(unsigned char), 1, arquivo);

    extrair_payload(arquivo, saida, arvore_huff, lixo);

    fclose(arquivo);
    fclose(saida);
}
