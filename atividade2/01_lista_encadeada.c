#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

void inserirPosicao(No **head, int valor, int posicao) {
    if (posicao < 0) {
        printf("posicao invalida\n");
        return;
    }

    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    // insere no inicio
    if (posicao == 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }

    No *atual = *head;
    for (int i = 0; i < posicao - 1; i++) {
        if (atual == NULL) {
            printf("posicao invalida\n");
            free(novo);
            return;
        }
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("posicao invalida\n");
        free(novo);
        return;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

// retorna a posicao do valor ou -1 se nao achar
int buscarValor(No *head, int valor) {
    int pos = 0;
    No *atual = head;
    while (atual != NULL) {
        if (atual->valor == valor) return pos;
        atual = atual->prox;
        pos++;
    }
    return -1;
}

void inverterLista(No **head) {
    No *ant = NULL;
    No *atual = *head;
    No *prox = NULL;

    while (atual != NULL) {
        prox = atual->prox;
        atual->prox = ant;
        ant = atual;
        atual = prox;
    }
    *head = ant;
}

// divide a lista ao meio usando ponteiro rapido e lento
void dividirLista(No *head, No **lista1, No **lista2) {
    if (head == NULL) {
        *lista1 = NULL;
        *lista2 = NULL;
        return;
    }

    No *lento = head;
    No *rapido = head->prox;

    while (rapido != NULL) {
        rapido = rapido->prox;
        if (rapido != NULL) {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }

    *lista1 = head;
    *lista2 = lento->prox;
    lento->prox = NULL;
}

void exibir(No *head) {
    while (head != NULL) {
        printf("%d -> ", head->valor);
        head = head->prox;
    }
    printf("NULL\n");
}

void liberar(No *head) {
    while (head != NULL) {
        No *temp = head;
        head = head->prox;
        free(temp);
    }
}

int main() {
    No *lista = NULL;

    printf("--- Parte 1: insercao em posicao ---\n");
    inserirPosicao(&lista, 10, 0);
    inserirPosicao(&lista, 20, 1);
    inserirPosicao(&lista, 30, 2);
    printf("lista: ");
    exibir(lista);
    inserirPosicao(&lista, 99, 1);
    printf("depois de inserir 99 na posicao 1: ");
    exibir(lista);

    printf("\n--- Parte 2: busca ---\n");
    printf("posicao do 99: %d\n", buscarValor(lista, 99));
    printf("posicao do 20: %d\n", buscarValor(lista, 20));
    printf("posicao do 50: %d\n", buscarValor(lista, 50));

    printf("\n--- Parte 3: inverter ---\n");
    printf("antes:  ");
    exibir(lista);
    inverterLista(&lista);
    printf("depois: ");
    exibir(lista);

    printf("\n--- Parte 4: dividir ---\n");
    liberar(lista);
    lista = NULL;
    inserirPosicao(&lista, 10, 0);
    inserirPosicao(&lista, 20, 1);
    inserirPosicao(&lista, 30, 2);
    inserirPosicao(&lista, 40, 3);
    inserirPosicao(&lista, 50, 4);
    printf("original: ");
    exibir(lista);

    No *l1 = NULL, *l2 = NULL;
    dividirLista(lista, &l1, &l2);
    printf("lista 1:  ");
    exibir(l1);
    printf("lista 2:  ");
    exibir(l2);

    printf("\n--- teste posicao invalida ---\n");
    No *teste = NULL;
    inserirPosicao(&teste, 1, 0);
    inserirPosicao(&teste, 2, 5);
    liberar(teste);

    liberar(l1);
    liberar(l2);
    return 0;
}
