#include "Huff.h"
#include "MinHeap.h"

#define TAM_FREQ 256

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
