#ifndef CABECALHO_H
#define CABECALHO_H

// Inclusões de bibliotecas
#include <stdio.h>
#include <stdlib.h>

// Definição do tamanho máximo
#define TAMANHO_MAXIMO 100

// Estrutura para representar um nó da lista encadeada
typedef struct No {
    int peso;
    struct No* proximo;
} No;

// Estrutura para representar uma pilha
typedef struct Pilha {
    No* topo;
} Pilha;

// Estrutura para representar uma fila
typedef struct Fila {
    No* frente;
    No* tras;
} Fila;

// Protótipos de funções
void inicializarPilha(Pilha* pilha);
void inicializarFila(Fila* fila);
void empilhar(Pilha* pilha, int peso);
int desempilhar(Pilha* pilha);
void enfileirar(Fila* fila, int peso);
int desenfileirar(Fila* fila);
void imprimeMatriz(int** matriz, int linhas, int colunas);
void somaMatriz(int** matriz, int linhas, int colunas);
void salvaVenda(Pilha* pilha, Fila* fila, int** matriz, int* linhaAtual);
void imprimirFila(Fila* fila);
int somaElementosFila(Fila* fila);
float mediaElementosFila(Fila* fila);

#endif /* CABECALHO_H */
