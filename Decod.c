#include "Cod.h"
#include "Huff.h"
#include "MinHeap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TAM_FREQ 256

void Decodificar(char Huff[]){
    int cont_bytes = 0;

    FILE *arquivo = fopen(Huff, "rb");

    fread(&cont_bytes, sizeof(int), 1, Huff);

    int frequencia[TAM_FREQ] = {0};

    for (int i = 0; i < cont_bytes; i++){
        unsigned char caractere;
        int frequenciaChar;

        fread(&caractere, sizeof(unsigned char), 1, Huff);
        fread(&frequencia, sizeof(int), 1, Huff);

        frequencia[caractere] = frequenciaChar;
    }

    
    
}
