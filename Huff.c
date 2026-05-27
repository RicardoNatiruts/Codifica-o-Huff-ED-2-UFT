#include "Huff.h"
#include "MinHeap.h"

#define TAM_FREQ 256

TNo* construir_arvore(unsigned int frequencias[256]) {
    TreeHuff *heap = criar_heap();

    for (int i = 0; i < 256; i++) {
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

void gerar_codigos(TNo *raiz, char *caminho, int profundidade, char codigos[256][512]) {
    if (!raiz) return;

    if (!raiz->esq && !raiz->dir) {
        caminho[profundidade] = '\0';
        strncpy(codigos[raiz->byte], caminho, 511);
        return;
    }

    caminho[profundidade] = '0';
    gerar_codigos(raiz->esq, caminho, profundidade + 1, codigos);

    caminho[profundidade] = '1';
    gerar_codigos(raiz->dir, caminho, profundidade + 1, codigos);
}

void liberar_arvore(TNo *raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int** create_dicionario(TreeHuff* tree) {
    
    // 1. Aloca um vetor de ponteiros (um para cada linha)
    int** dicionario = (int**)malloc(TAM_FREQ * sizeof(int*));
    
    // 2. Aloca o vetor de inteiros para cada linha individualmente
    for(int i = 0; i < TAM_FREQ; i++) {
        dicionario[i] = (int*)malloc(TAM_FREQ * sizeof(int));
    }

    int* auxilar = (int*)malloc(TAM_FREQ * sizeof(int*));
    
    int cont = 0;

    criarCaminho(dicionario, auxilar, tree->root, cont);
    
    return dicionario;
}
