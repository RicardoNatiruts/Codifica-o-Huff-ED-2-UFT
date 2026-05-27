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

TNo* criar_no(unsigned char byte, unsigned int frequencia);
TreeHuff* criar_heap();
void trocar_nos(TNo **a, TNo** b);
void min_heapify(TreeHuff* heap, int indice);
void inserir_min_heap(TreeHuff* heap, TNo* no);
TNo* extrair_minimo(TreeHuff* heap);


#endif
