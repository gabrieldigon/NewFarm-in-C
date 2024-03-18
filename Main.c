#include "Cabecalho.h"

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
