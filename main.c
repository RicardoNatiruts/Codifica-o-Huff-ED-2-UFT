#include "Cod.h"
#include "MinHeap.h"
#include "Huff.h"
#define ARQUIVO "paralelepipedo.txt"

int main(){
    unsigned int bits_totais = 0;
    unsigned int bits_lixo;
    FILE *arquivo = fopen("codificado.huff", "wb");

    unsigned int frequencia[MAX_NOS] = {0};
    unsigned int contagem = 0;

    preencher_tabela(frequencia, ARQUIVO);
    imprimir_tabela(frequencia);

    TNo* arvore = construir_arvore(frequencia);
    int** dicionario = create_dicionario(arvore);

    for (int i = 0; i < MAX_NOS; i++) {
        if(frequencia[i] > 0){
            contagem++;
            printf("Letra '%c': ", i);
        
        
        int j = 0;
        while (dicionario[i][j] != -1) {
            printf("%d", dicionario[i][j]);
            bits_totais += frequencia[i];
            j++;
        }
        printf("\n");

        }
    }

    printf("bits totais: %u\n", bits_totais);
    if(bits_totais % 8 == 0){
        bits_lixo = 0;
    }else{
        bits_lixo = 8 - (bits_totais%8);
    }
    printf("bits lixo: %u", bits_lixo);

    fwrite(&contagem, sizeof(int), 1, arquivo);
    for(int i = 0; i < MAX_NOS; i++){
        if(frequencia[i] > 0){
            unsigned char caractere = (unsigned char)i;
            fwrite(&caractere, sizeof(unsigned char), 1, arquivo);
            fwrite(&frequencia[i], sizeof(int), 1, arquivo);
        }
    }
    fwrite(&bits_lixo, sizeof(unsigned char), 1, arquivo);

    FILE *arquivo_leitura = fopen(ARQUIVO, "r");

    unsigned char byte_buffer = 0;
    int contador_bits = 0;         
    int c;

    while ((c = fgetc(arquivo_leitura)) != EOF) {
        
        int j = 0;
        while (dicionario[c][j] != -1) {
            int bit = dicionario[c][j];

            byte_buffer = (byte_buffer << 1) | bit;
            contador_bits++;

            if (contador_bits == 8) {
                fwrite(&byte_buffer, sizeof(unsigned char), 1, arquivo);
                byte_buffer = 0;    
                contador_bits = 0;   
            }
            j++;
        }
    }

    if (contador_bits > 0) {
        byte_buffer = byte_buffer << (8 - contador_bits);
        fwrite(&byte_buffer, sizeof(unsigned char), 1, arquivo);
    }

    fclose(arquivo_leitura);
    fclose(arquivo);

    return 0;
}
