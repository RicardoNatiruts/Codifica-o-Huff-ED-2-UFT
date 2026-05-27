#include "Cod.h"
#include "MinHeap.h"
#define ARQUIVO "casmurro.txt"

int main(){

    unsigned int frequencia[MAX_NOS] = {0};

    preencher_tabela(frequencia, ARQUIVO);
    imprimir_tabela(frequencia);

    return 0;
}
