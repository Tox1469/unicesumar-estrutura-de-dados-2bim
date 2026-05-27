#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10

typedef struct No {
    char palavra[100];
    char definicao[300];
    struct No *prox;
} No;

typedef struct {
    No *lista;
} Bucket;

typedef struct {
    Bucket tabela[TAMANHO];
    int total;
    int colisoes;
} TabelaHash;

// funcao hash: soma os valores ascii dos caracteres
int hash(char *palavra) {
    int soma = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        soma += palavra[i];
    }
    return soma % TAMANHO;
}

void inicializar(TabelaHash *th) {
    for (int i = 0; i < TAMANHO; i++) {
        th->tabela[i].lista = NULL;
    }
    th->total = 0;
    th->colisoes = 0;
}

void inserir(TabelaHash *th, char *palavra, char *definicao) {
    int idx = hash(palavra);

    // verifica se a palavra ja existe, se sim so atualiza a definicao
    No *atual = th->tabela[idx].lista;
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            strncpy(atual->definicao, definicao, 299);
            printf("'%s' atualizada\n", palavra);
            return;
        }
        atual = atual->prox;
    }

    // se ja tem elemento nesse bucket, conta como colisao
    if (th->tabela[idx].lista != NULL) {
        th->colisoes++;
    }

    No *novo = malloc(sizeof(No));
    strncpy(novo->palavra, palavra, 99);
    strncpy(novo->definicao, definicao, 299);
    novo->prox = th->tabela[idx].lista;
    th->tabela[idx].lista = novo;
    th->total++;
    printf("'%s' inserida\n", palavra);
}

No *buscar(TabelaHash *th, char *palavra) {
    int idx = hash(palavra);
    No *atual = th->tabela[idx].lista;
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void remover(TabelaHash *th, char *palavra) {
    int idx = hash(palavra);
    No *atual = th->tabela[idx].lista;
    No *ant = NULL;

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            if (ant == NULL) {
                th->tabela[idx].lista = atual->prox;
            } else {
                ant->prox = atual->prox;
            }
            free(atual);
            th->total--;
            printf("'%s' removida\n", palavra);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
    printf("'%s' nao encontrada\n", palavra);
}

void exibir(TabelaHash *th) {
    printf("\n--- tabela hash ---\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("[%2d]: ", i);
        No *atual = th->tabela[i].lista;
        if (atual == NULL) {
            printf("(vazio)\n");
        } else {
            while (atual != NULL) {
                printf("'%s'", atual->palavra);
                if (atual->prox != NULL) printf(" -> ");
                atual = atual->prox;
            }
            printf("\n");
        }
    }
}

void estatisticas(TabelaHash *th) {
    int maior = 0;
    for (int i = 0; i < TAMANHO; i++) {
        int tam = 0;
        No *atual = th->tabela[i].lista;
        while (atual != NULL) {
            tam++;
            atual = atual->prox;
        }
        if (tam > maior) maior = tam;
    }

    printf("\n--- estatisticas ---\n");
    printf("elementos:      %d\n", th->total);
    printf("colisoes:       %d\n", th->colisoes);
    printf("fator de carga: %.2f\n", (float)th->total / TAMANHO);
    printf("maior lista:    %d elemento(s)\n", maior);
}

int main() {
    TabelaHash th;
    inicializar(&th);

    inserir(&th, "compilador", "programa que traduz codigo fonte para linguagem de maquina");
    inserir(&th, "ponteiro", "variavel que armazena um endereco de memoria");
    inserir(&th, "recursao", "funcao que chama a si mesma para resolver um problema menor");
    inserir(&th, "struct", "estrutura que agrupa variaveis de tipos diferentes");
    inserir(&th, "malloc", "funcao que aloca memoria dinamicamente no heap");
    inserir(&th, "lista", "estrutura de dados linear com nos encadeados");
    inserir(&th, "pilha", "estrutura LIFO - ultimo a entrar primeiro a sair");
    inserir(&th, "fila", "estrutura FIFO - primeiro a entrar primeiro a sair");

    exibir(&th);
    estatisticas(&th);

    printf("\n--- buscas ---\n");
    No *res = buscar(&th, "ponteiro");
    if (res != NULL)
        printf("encontrado: %s = %s\n", res->palavra, res->definicao);

    res = buscar(&th, "arvore");
    if (res == NULL)
        printf("'arvore' nao encontrada\n");

    printf("\n--- remocoes ---\n");
    remover(&th, "lista");
    remover(&th, "arvore");

    exibir(&th);
    estatisticas(&th);

    return 0;
}
