#include <stdio.h>

// conta quantas vezes a funcao eh chamada
long long fibonacci(int n, int *cont) {
    (*cont)++;
    // caso base: fib(0) = 0 e fib(1) = 1
    if (n <= 1) return n;
    return fibonacci(n - 1, cont) + fibonacci(n - 2, cont);
}

int main() {
    int n;
    printf("Digite o valor de n: ");
    scanf("%d", &n);

    int cont = 0;
    long long resultado = fibonacci(n, &cont);

    printf("fib(%d) = %lld\n", n, resultado);
    printf("total de chamadas: %d\n", cont);

    // mostra a serie de 0 ate n
    printf("\nSerie completa:\n");
    for (int i = 0; i <= n; i++) {
        int c = 0;
        printf("  fib(%d) = %lld\n", i, fibonacci(i, &c));
    }

    return 0;
}
