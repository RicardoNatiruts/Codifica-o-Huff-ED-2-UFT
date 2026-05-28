# Codificação de Huffman - ED2 (UFT)

Este projeto implementa o algoritmo de **Codificação de Huffman** em C, uma técnica de compressão de dados sem perdas. O programa permite compactar arquivos de texto (ou qualquer outro tipo de arquivo binário) gerando um arquivo comprimido, e também descompactá-lo de volta ao seu formato original.

## Integrantes
- Ricardo Rocha Alves
- Tarciso Filho de Mir. Dias
- Guilherme da Silva Santos

## 📁 Organização dos Arquivos

O projeto foi dividido em módulos (headers e sources) para garantir organização e fácil manutenção.

```text
📂 Projeto
┣ 📜 main.c       # Ponto de entrada do programa, gerencia argumentos de linha de comando
┣ 📜 Cod.c        # Lógica principal de codificação/compressão
┣ 📜 Cod.h        # Cabeçalho de codificação
┣ 📜 Decod.c      # Lógica principal de decodificação/descompressão
┣ 📜 Decod.h      # Cabeçalho de decodificação
┣ 📜 MinHeap.c    # Implementação da Fila de Prioridade (Min-Heap)
┣ 📜 MinHeap.h    # Cabeçalho da Min-Heap
┣ 📜 Huff.c       # Lógica de criação da Árvore de Huffman e Dicionário
┣ 📜 Huff.h       # Cabeçalho da Árvore de Huffman
┗ 📜 README.md    # Documentação do projeto (este arquivo)
```

## 🚀 Como Compilar e Executar

### Compilação
Para compilar o projeto, você pode usar o `gcc`. No terminal, navegue até a pasta do projeto e execute:
```bash
gcc main.c Cod.c Decod.c MinHeap.c Huff.c -o huffman
```

### Execução
O programa exige 4 argumentos na linha de comando: a chamada do programa, a flag de operação (`-c` para compactar ou `-d` para descompactar), o arquivo de entrada e o arquivo de saída.

**Para compactar um arquivo:**
```bash
./huffman -c arquivo_original.txt arquivo_compactado.huff
```

**Para descompactar um arquivo:**
```bash
./huffman -d arquivo_compactado.huff arquivo_recuperado.txt
```

---

## Informações de Cabeçalho
| Campo | Tamanho | Descrição |
|---|---|---|
| Contagem | 4 bytes (int) | Quantidade de bytes únicos na tabela |
| Tabela | N × 5 bytes | Pares `[Byte (1 byte) + Frequência (4 bytes)]` |
| Bits Lixo | 1 byte | Bits não usados no último byte (0 a 7) |
| Payload | Variável | Linguição de Bits |

## 🧩 Os 4 Eixos do Algoritmo

A implementação foi dividida em quatro módulos lógicos (eixos) para facilitar a manutenção e organização do código:

### 1. Codificação (`Cod.c` e `Cod.h`)
Responsável pelo processo de compressão dos dados. 
- Lê o arquivo de entrada e contabiliza a frequência de cada byte (caractere).
- Coordena a criação da Árvore de Huffman e do dicionário de caminhos (bits).
- Escreve o cabeçalho no arquivo de saída (tamanho, frequências e bits de lixo).
- Converte os bytes originais em suas respectivas sequências de bits do dicionário e salva no arquivo final compactado.

### 2. Decodificação (`Decod.c` e `Decod.h`)
Responsável por reverter o processo de compressão.
- Lê o cabeçalho do arquivo compactado para recuperar a tabela de frequências e reconstruir a mesma Árvore de Huffman gerada na compressão.
- Navega na árvore bit a bit (0 para a esquerda, 1 para a direita) lendo o "payload" (dados comprimidos).
- Ao encontrar um "nó folha", extrai o byte original e o escreve no arquivo de saída, restaurando perfeitamente o arquivo.

### 3. Min-Heap / Fila de Prioridade (`MinHeap.c` e `MinHeap.h`)
A estrutura de dados base para construir a Árvore de Huffman de forma eficiente.
- Implementa uma Fila de Prioridade usando uma Min-Heap, onde os elementos de menor frequência sempre ficam no topo (raiz da heap).
- Fornece funções de inserção (`inserir_min_heap`) e extração do menor elemento (`extrair_minimo`).
- Garante o desempenho necessário (tempo `O(log n)`) na hora de pegar os dois nós menos frequentes durante a construção da árvore.

### 4. Árvore de Huffman (`Huff.c` e `Huff.h`)
Responsável pela manipulação da estrutura em árvore.
- Constrói a árvore de Huffman chamando a `MinHeap`. Ele junta progressivamente os dois nós de menor frequência da heap, criando um nó pai com a soma das frequências, até sobrar apenas a raiz geral da árvore.
- Gera o Dicionário (`create_dicionario`): Percorre a árvore recursivamente salvando o caminho feito até cada folha (0 à esquerda, 1 à direita), gerando as novas representações binárias compactadas para cada byte.

## Tabela de Resultados

| Arquivo | Tamanho Original | Compactado | Taxa de Compactação |
| :--- | :---: | :---: |:--- |
| **Bíblia.txt** | 4,3 MB | 2,5 MB | Aprox. 41,86% |
| **LogoMarca** | 456 KB | 457 KB | Aumento de Aprox. 0,22% |
| **TextoRepetição.txt** | 24 KB | 6 KB | 75% |
| **Parelelepipedo** | 14 bytes | 50 KB | Aumento de Aprox. 257% |
