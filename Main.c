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

void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

void inicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

void empilhar(Pilha* pilha, int peso) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->peso = peso;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

int desempilhar(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("Erro: Pilha vazia.\n");
        exit(EXIT_FAILURE);
    }
    No* temp = pilha->topo;
    int peso = temp->peso;
    pilha->topo = temp->proximo;
    free(temp);
    return peso;
}

void enfileirar(Fila* fila, int peso) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->peso = peso;
    novoNo->proximo = NULL;
    if (fila->frente == NULL) {
        fila->frente = novoNo;
    } else {
        fila->tras->proximo = novoNo;
    }
    fila->tras = novoNo;
}

int desenfileirar(Fila* fila) {
    if (fila->frente == NULL) {
        printf("Erro: Fila vazia.\n");
        exit(EXIT_FAILURE);
    }
    No* temp = fila->frente;
    int peso = temp->peso;
    fila->frente = temp->proximo;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    free(temp);
    return peso;
}

void imprimeMatriz(int** matriz, int linhas, int colunas) {
    printf("\nCabecas de gado da fazenda:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] != 0) {
                printf("%d \n", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

void somaMatriz(int** matriz, int linhas, int colunas) {
    printf("Soma dos pesos das cabecas de gado da fazenda:\n");
    float soma = 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] != 0) {
                soma += matriz[i][j];
            }
        }
    }
    printf("%.0f Kg \n\n", soma);
    printf("Valor total do gado na fazenda considerando arroba 207 R$\n");
    float calculoTotal = (soma / 30) * 207;
    printf("%.2f\n", calculoTotal);
}

void salvaVenda(Pilha* pilha, Fila* fila, int** matriz, int* linhaAtual) {
    int peso;
    while (1) {
        printf("Digite o peso do boi (Digite -1 para encerrar): ");
        scanf("%d", &peso);
        if (peso == -1)
            break;
        empilhar(pilha, peso);
        enfileirar(fila, peso);
    }
    for (int i = 0; i < TAMANHO_MAXIMO && pilha->topo != NULL; i++) {
        matriz[*linhaAtual][i] = desempilhar(pilha);
    }
    (*linhaAtual)++;
}

void imprimirFila(Fila* fila) {
    printf("\nElementos na fila:\n");
    No* atual = fila->frente;
    while (atual != NULL) {
        printf("%d\n", atual->peso);
        atual = atual->proximo;
    }
}
int somaElementosFila(Fila* fila) {
    int soma = 0;
    No* atual = fila->frente;
    while (atual != NULL) {
        soma += atual->peso;
        atual = atual->proximo;
    }
    return soma;
}

float mediaElementosFila(Fila* fila) {
    int soma = 0;
    int contador = 0;
    No* atual = fila->frente;
    
    // Percorre a fila para calcular a soma e contar o número de elementos
    while (atual != NULL) {
        soma += atual->peso;
        contador++;
        atual = atual->proximo;
    }
    
    // Verifica se a fila está vazia para evitar divisão por zero
    if (contador == 0) {
        return 0; // Retorna 0 se a fila estiver vazia
    }
    
    // Calcula a média
    float media = (float)soma / contador;
    return media;
}




int main() {
    const int tamanhoMaximo = TAMANHO_MAXIMO;
    int** matrizVendas = (int**)malloc(tamanhoMaximo * sizeof(int*));
    for (int i = 0; i < tamanhoMaximo; i++) {
        matrizVendas[i] = (int*)malloc(tamanhoMaximo * sizeof(int));
    }

    int linhaAtual = 0;
    int escolha;

    do {
        printf("\nOrganizador de Fazendas\n");
        printf("\nDigite\n-1 para registrar uma venda\n-2 para ver o resultado total da fazenda \n-3 Para Sair\n");
        scanf("%d", &escolha);

        if (escolha == 1) {
            Pilha pilha;
            Fila fila;
            inicializarPilha(&pilha);
            inicializarFila(&fila);

            salvaVenda(&pilha, &fila, matrizVendas, &linhaAtual);
            imprimirFila(&fila);
            float soma = somaElementosFila(&fila);
            printf("\nSoma do peso total da venda: %.0f \n ", soma);

            float media = mediaElementosFila(&fila);
            printf("\nMedia de peso da venda : %.2f\n ", media);

            printf("\nQuantidade de arrobas totais\n");
            float pesoTotalEmArrobas = soma / 30;
            printf("%.2f ", pesoTotalEmArrobas);

            printf("\nMedia de arrobas de uma cabeca\n");
            float mediaDeArrobas = media / 30;
            printf("R$ %.2f ", mediaDeArrobas);

            printf("\nValor total (considerando a arroba 207 R$)\n");
            float valorTotal = pesoTotalEmArrobas * 207.00;
            printf("R$ %.2f \n\n", valorTotal);

        } else if (escolha == 2) {
            imprimeMatriz(matrizVendas, linhaAtual, tamanhoMaximo);
            somaMatriz(matrizVendas, linhaAtual, tamanhoMaximo);
        }

    } while (escolha != 3);

    for (int i = 0; i < tamanhoMaximo; i++) {
        free(matrizVendas[i]);
    }
    free(matrizVendas);

    printf("Obrigado por utilizar, volte sempre!");

    return 0;
}
