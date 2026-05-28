#include "MinHeap.h"

TNo *criar_no(unsigned char byte, unsigned int frequencia) {
    TNo *novo_no = (TNo *)malloc(sizeof(TNo));
    novo_no->byte = byte;
    novo_no->frequencia = frequencia;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

TreeHuff *criar_heap() {
    TreeHuff *heap = (TreeHuff *)malloc(sizeof(TreeHuff));
    heap->tamanho = 0;
    heap->root = (TNo **)malloc(MAX_NOS * sizeof(TNo *)); //Alocar apenas 256

    return heap;
}

void trocar_nos(TNo** a, TNo** b) {
    TNo* temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(TreeHuff* heap, int indice) {
    int menor = indice; 
    int esquerda = 2 * indice + 1; 
    int direita = 2 * indice + 2; 

    //Se o filho da esuerda existe e tiver a freq menor que o no indice (atual), troca.
    if (esquerda < heap->tamanho && 
        heap->root[esquerda]->frequencia < heap->root[menor]->frequencia) {
        menor = esquerda;
    }

    //Se o filho da direita existe e tiver a freq menor que o no indice (atual), troca.
    if (direita < heap->tamanho && 
        heap->root[direita]->frequencia < heap->root[menor]->frequencia) {
        menor = direita;
    }

    if (menor != indice) {
        trocar_nos(&heap->root[indice], &heap->root[menor]);
        min_heapify(heap, menor);
    }
}

void inserir_min_heap(TreeHuff* heap, TNo* no){
    if (heap->tamanho >= MAX_NOS){
        printf ("Heap cheia.\n");
        return;
    }

    int i = heap->tamanho;
    int pai = (i - 1) / 2;
    heap->tamanho++;
    heap->root[i] = no;

    while (i > 0 && heap->root[i]->frequencia <= heap->root[pai]->frequencia) {
        trocar_nos(&heap->root[i], &heap->root[pai]);
        
        i = pai;
        pai = (i - 1) / 2;
    }
}

TNo* extrair_minimo(TreeHuff* heap) {
    if (heap->tamanho == 0) {
        return NULL; 
    }

    TNo* minimo = heap->root[0];

    heap->root[0] = heap->root[heap->tamanho - 1];
    heap->tamanho--;
    min_heapify(heap, 0);

    return minimo;
}