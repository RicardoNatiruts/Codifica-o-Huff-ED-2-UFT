#ifndef MINHEAP_H
#define MINHEAP_H
#include <stdlib.h>
#include <stdio.h>

#define MAX_NOS 256

typedef struct TNo {
    unsigned char byte;
    unsigned int frequencia;
    struct TNo *esq; 
    struct TNo *dir; 
} TNo;

typedef struct TreeHuff {
    int tamanho;
    TNo **root; 
} TreeHuff;


#endif
