#ifndef HUFF_H
#define HUFF_H

#include "MinHeap.h"

int** create_dicionario(TreeHuff*);

TNo* construir_arvore(unsigned int frequencias[256]);

void gerar_codigos(TNo *raiz, char *caminho, int profundidade, char codigos[256][512]);

void liberar_arvore(TNo *raiz);

#endif