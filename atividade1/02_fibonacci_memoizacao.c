#include <stdio.h>
#include <stdlib.h>

// fibonacci sem cache pra comparar depois
long long fib_sem_memo(int n, int *cont) {
    (*cont)++;
    if (n <= 1) return n;
    return fib_sem_memo(n - 1, cont) + fib_sem_memo(n - 2, cont);
}

// fibonacci com memoizacao, guarda os resultados ja calculados
long long fib_memo(int n, long long *cache, int *cont) {
    (*cont)++;
    if (n <= 1) return n;
    // se ja calculou esse valor antes, retorna do cache
    if (cache[n] != -1) return cache[n];
    cache[n] = fib_memo(n - 1, cache, cont) + fib_memo(n - 2, cache, cont);
    return cache[n];
}

int main() {
    int n;
    printf("Digite n: ");
    scanf("%d", &n);

    // aloca o cache com malloc
    long long *cache = malloc((n + 1) * sizeof(long long));
    for (int i = 0; i <= n; i++) cache[i] = -1;

    int cont_memo = 0;
    long long resultado = fib_memo(n, cache, &cont_memo);

    int cont_sem = 0;
    fib_sem_memo(n, &cont_sem);

    printf("fib(%d) = %lld\n", n, resultado);
    printf("chamadas com memoizacao: %d\n", cont_memo);
    printf("chamadas sem memoizacao: %d\n", cont_sem);

    free(cache);
    return 0;
}
