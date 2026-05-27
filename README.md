# Estruturas de Dados - 2BIM

**Integrantes:** Luis Boratto, Igor Palliser

---

## Atividade 1 - Recursividade

### Exercicio 1 - Fibonacci sem otimizacao
Implementa o fibonacci de forma recursiva simples, sem nenhuma otimizacao. O programa mostra o resultado e a quantidade total de chamadas recursivas feitas, o que deixa claro como o numero de chamadas cresce muito rapido.

### Exercicio 2 - Fibonacci com memoizacao
Refaz o fibonacci usando um cache alocado dinamicamente com malloc. Guarda os resultados ja calculados pra nao recalcular de novo. No final compara o numero de chamadas com a versao sem otimizacao.

### Exercicio 3 - Torres de Hanoi
Resolve as torres de hanoi recursivamente. Recebe o numero de discos, mostra cada movimento passo a passo e o total no final.

---

## Atividade 2 - Listas Encadeadas

### Partes 1 a 4
Implementacoes com lista encadeada simples:

- **inserirPosicao**: insere um valor em qualquer posicao da lista (trata lista vazia, inicio, meio e fim)
- **buscarValor**: percorre a lista e retorna a posicao do valor, ou -1 se nao encontrar
- **inverterLista**: inverte a lista usando so ponteiros, sem criar nova lista ou vetor auxiliar
- **dividirLista**: divide a lista ao meio usando ponteiro rapido e lento, sem contar os elementos antes

### Parte 5 - Playlist circular
Playlist de musicas usando lista circular duplamente encadeada. Tem navegacao pra frente e pra tras, exibicao de todas as musicas e controle pra nao entrar em loop infinito na hora de percorrer.
