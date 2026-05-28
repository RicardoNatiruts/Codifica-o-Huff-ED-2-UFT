#include "Huff.h"
#include "MinHeap.h"
#include <string.h>

#define TAM_FREQ 256

TNo* construir_arvore(unsigned int frequencias[]) {
    TreeHuff *heap = criar_heap();

    for (int i = 0; i < TAM_FREQ; i++) {
        if (frequencias[i] > 0) {
            inserir_min_heap(heap, criar_no((unsigned char)i, frequencias[i]));
        }
    }

    if (heap->tamanho == 1) {
        TNo *unico = extrair_minimo(heap);
        TNo *raiz  = criar_no(0, unico->frequencia);
        raiz->esq  = unico;
        free(heap->root);
        free(heap);
        return raiz;
    }

    while (heap->tamanho > 1) {
        TNo *esq = extrair_minimo(heap);
        TNo *dir = extrair_minimo(heap);
        TNo *pai = criar_no(0, esq->frequencia + dir->frequencia);
        pai->esq = esq;
        pai->dir = dir;
        inserir_min_heap(heap, pai);
    }

    TNo *raiz = extrair_minimo(heap);
    free(heap->root);
    free(heap);
    return raiz;
}

void criarCaminho(int** dicionario, int* auxiliar, TNo* root, int cont){
    if(!root->esq && !root->dir){
        auxiliar[cont] = -1;
        int i = 0;
        for (int i = 0; i <= cont; i++) {
            dicionario[root->byte][i] = auxiliar[i];
        }
    }

    if(root->esq){
        auxiliar[cont] = 1;
        criarCaminho(dicionario, auxiliar, root->esq, cont+1);
    }
    if(root->dir){
        auxiliar[cont] = 0;
        criarCaminho(dicionario, auxiliar, root->dir, cont+1);
    }
    return;
}

int** create_dicionario(TNo* root) { 
    int** dicionario = (int**)malloc(TAM_FREQ * sizeof(int*));
    for(int i = 0; i < TAM_FREQ; i++) {
        dicionario[i] = (int*)malloc(TAM_FREQ * sizeof(int));
        for(int j = 0; j < TAM_FREQ; j++) dicionario[i][j] = -1;
    }

    int* auxiliar = (int*)malloc(TAM_FREQ * sizeof(int)); 
    int cont = 0;

    criarCaminho(dicionario, auxiliar, root, cont); 
    
    free(auxiliar);
    return dicionario;
}
