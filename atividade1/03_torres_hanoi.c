#include <stdio.h>

void hanoi(int n, char origem, char destino, char aux, int *mov) {
    // caso base: so tem um disco, move direto
    if (n == 1) {
        printf("move disco 1: %c -> %c\n", origem, destino);
        (*mov)++;
        return;
    }
    // move os n-1 discos pra torre auxiliar
    hanoi(n - 1, origem, aux, destino, mov);
    printf("move disco %d: %c -> %c\n", n, origem, destino);
    (*mov)++;
    // move os n-1 discos do auxiliar pro destino
    hanoi(n - 1, aux, destino, origem, mov);
}

int main() {
    int n;
    printf("Quantos discos? ");
    scanf("%d", &n);

    int mov = 0;
    hanoi(n, 'A', 'C', 'B', &mov);
    printf("\nTotal de movimentos: %d\n", mov);

    return 0;
}
