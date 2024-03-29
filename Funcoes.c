#include "Cabecalho.h"
// funcoes de incialização da pilha
void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

void inicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

//funcoes basicas para montar as TADS
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
// Essa func imprime a matriz com o peso de todas as cabeças de gado da fazenda, ela e populada pela pilha na funcao salvarVenda
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
//soma o peso de todas as cabeças de gado da fazenda
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
// essa função talvez seja a mais importante, pega os elementos que o usuario digita ao fazer uma venda e salva em uma pilha e em uma fila, depois usa a pilha pra popular a matriz, ja a fila fica responsavel por levar os dados ate a main para serem impressos e gerarem um status de venda
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
//imprime os elementos de uma fila
void imprimirFila(Fila* fila) {
    printf("\nElementos na fila:\n");
    No* atual = fila->frente;
    while (atual != NULL) {
        printf("%d\n", atual->peso);
        atual = atual->proximo;
    }
}
// soma os elementos de uma fila
int somaElementosFila(Fila* fila) {
    int soma = 0;
    No* atual = fila->frente;
    while (atual != NULL) {
        soma += atual->peso;
        atual = atual->proximo;
    }
    return soma;
}
// faz a media de elementos de uma fila
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
