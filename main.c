#include "Cod.h"
#include "MinHeap.h"
#include "Huff.h"
#include "Decod.h"
#define ARQUIVO "casmurro.txt"

int main(){

    unsigned int frequencia[MAX_NOS] = {0};

    preencher_tabela(frequencia, ARQUIVO);
    imprimir_tabela(frequencia);

    TNo* arvore = construir_arvore(frequencia);
    int** dicionario = create_dicionario(arvore);

    Codificar(ARQUIVO, "codificado.huff", dicionario, frequencia);

    Decodificar("codificado.huff", "decodificado.huff");

    return 0;
}
