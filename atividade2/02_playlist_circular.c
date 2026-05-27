#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char musica[100];
    struct No *prox;
    struct No *ant;
} No;

void adicionarMusica(No **head, char *nome) {
    No *novo = malloc(sizeof(No));
    strncpy(novo->musica, nome, 99);
    novo->musica[99] = '\0';

    if (*head == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        *head = novo;
        return;
    }

    // insere no final mantendo a circularidade
    No *ultimo = (*head)->ant;
    ultimo->prox = novo;
    novo->ant = ultimo;
    novo->prox = *head;
    (*head)->ant = novo;
}

void proximaMusica(No **atual) {
    if (*atual != NULL)
        *atual = (*atual)->prox;
}

void musicaAnterior(No **atual) {
    if (*atual != NULL)
        *atual = (*atual)->ant;
}

void exibirPlaylist(No *head) {
    if (head == NULL) {
        printf("playlist vazia\n");
        return;
    }
    No *atual = head;
    do {
        printf("[%s]", atual->musica);
        if (atual->prox != head) printf(" <-> ");
        atual = atual->prox;
    } while (atual != head);
    printf(" <-> (volta pro inicio)\n");
}

int totalMusicas(No *head) {
    if (head == NULL) return 0;
    int total = 0;
    No *atual = head;
    do {
        total++;
        atual = atual->prox;
    } while (atual != head);
    return total;
}

void liberarPlaylist(No **head) {
    if (*head == NULL) return;
    No *atual = (*head)->prox;
    while (atual != *head) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(*head);
    *head = NULL;
}

int main() {
    No *playlist = NULL;
    No *atual = NULL;

    adicionarMusica(&playlist, "Rock");
    adicionarMusica(&playlist, "Jazz");
    adicionarMusica(&playlist, "Pop");

    printf("playlist:\n");
    exibirPlaylist(playlist);
    printf("total: %d musicas\n\n", totalMusicas(playlist));

    printf("navegando pra frente:\n");
    atual = playlist;
    printf("  tocando: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("  tocando: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("  tocando: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("  tocando: %s (voltou pro inicio)\n", atual->musica);

    printf("\nnavegando pra tras:\n");
    musicaAnterior(&atual);
    printf("  voltou pra: %s\n", atual->musica);

    // percorre todas sem loop infinito
    printf("\ntodas as musicas:\n");
    No *inicio = playlist;
    atual = playlist;
    int i = 1;
    do {
        printf("  %d. %s\n", i++, atual->musica);
        proximaMusica(&atual);
    } while (atual != inicio);

    liberarPlaylist(&playlist);
    return 0;
}
