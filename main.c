#include "Cod.h"
#include "MinHeap.h"
#include "Huff.h"
#include "Decod.h"
#define ARQUIVO "casmurro.txt"

int main(){

    

    

    Codificar(ARQUIVO, "codificado.huff");

    Decodificar("codificado.huff", "decodificado.txt");

    return 0;
}
