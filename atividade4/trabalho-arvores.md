# Trabalho de Estrutura de Dados – Árvores Avançadas

> Atividade Avaliativa 4 – 2º Bimestre
>
> Integrantes: Luis Boratto e Igor Pallisser

## Introdução

Quando a gente começa a estudar árvores, normalmente para na árvore binária de busca comum. O problema é que essa estrutura, sozinha, não garante que vai continuar eficiente. Se os dados forem inseridos já mais ou menos ordenados, a árvore "degenera" e vira praticamente uma lista ligada, perdendo toda a vantagem do tempo logaritmico. É justamente pra resolver isso que existem as árvores balanceadas e as variações que estudamos neste trabalho.

Aqui a gente trata de três estruturas: a árvore AVL, a árvore Rubro-Negra (Red-Black) e a árvore N-ária. As duas primeiras resolvem o problema do balanceamento de maneiras diferentes, e a terceira muda a ideia de quantos filhos um nó pode ter.

---

## Parte 1 – Pesquisa sobre os tipos de árvore

### Árvore AVL

**Conceito.** A AVL é uma árvore binária de busca que se mantém balanceada de forma automática. O nome vem dos dois pesquisadores russos que a propuseram em 1962 (Adelson-Velsky e Landis). A regra que ela segue é simples de enunciar: para qualquer nó, a diferença de altura entre a subárvore da esquerda e a da direita nunca pode ser maior que 1.

Essa diferença tem até um nome, o **fator de balanceamento**, calculado como `altura(esquerda) - altura(direita)`. Enquanto esse valor fica em -1, 0 ou +1, está tudo certo. Quando uma inserção ou remoção faz o fator passar disso, a árvore aplica rotações para se ajustar de novo (as rotações estão explicadas na Parte 2).

**Características.**
- É sempre uma árvore binária de busca (cada nó tem no máximo dois filhos, e a chave da esquerda é menor e a da direita é maior).
- Guarda, em cada nó, a informação de altura ou do fator de balanceamento.
- Se reorganiza sozinha a cada inserção/remoção que quebre a regra.
- É considerada uma árvore "rigidamente" balanceada, porque a condição de altura é bem apertada.

**Vantagens.**
- Busca, inserção e remoção sempre em O(log n), mesmo no pior caso.
- Como o balanceamento é rígido, ela costuma ficar mais "baixinha" que a Rubro-Negra, então as buscas tendem a ser um pouco mais rápidas.
- Ótima para situações em que a gente busca muito mais do que insere.

**Desvantagens.**
- Justamente por ser rígida, ela precisa fazer rotações com mais frequência. Isso deixa a inserção e a remoção um pouco mais custosas.
- O código fica mais trabalhoso de implementar do que o de uma árvore binária comum.

**Exemplo ilustrado.** Se a gente inserir as chaves 15, 25 e 40 nessa ordem numa árvore binária comum, ela "cai" toda para a direita:

```
   15
     \
      25
        \
         40
```

A AVL percebe que o nó 15 ficou com fator de balanceamento -2 (desbalanceado) e faz uma rotação. O resultado é uma árvore equilibrada:

```
      25
     /  \
   15    40
```

### Árvore Rubro-Negra (Red-Black)

**Conceito.** A Rubro-Negra também é uma árvore binária de busca que se balanceia sozinha, mas usa uma ideia diferente da AVL: em vez de controlar altura diretamente, ela pinta cada nó de **vermelho** ou **preto** e segue um conjunto de regras de cor. Mantendo essas cores em ordem, ela garante que o caminho mais longo da raiz até uma folha nunca seja mais que o dobro do caminho mais curto. Ou seja, ela nao fica perfeitamente balanceada como a AVL, mas fica "balanceada o suficiente".

**Regras de coloração (as propriedades).**
1. Todo nó é vermelho ou preto.
2. A raiz é sempre preta.
3. Toda folha (os nós nulos, chamados de NIL) é considerada preta.
4. Se um nó é vermelho, os dois filhos dele têm que ser pretos (ou seja, não pode haver dois vermelhos seguidos).
5. Partindo de qualquer nó, todos os caminhos até as folhas passam pela mesma quantidade de nós pretos. Esse número é chamado de "altura negra".

São essas cinco regras que mantêm o equilíbrio. Quando uma inserção quebra alguma delas, a árvore corrige com **recolorações** (trocar a cor de alguns nós) e, quando a recoloração não basta, com **rotações**.

**Características.**
- Cada nó guarda um bit extra de informação: a cor.
- O balanceamento é mais "frouxo" que o da AVL, o que dá menos rotações.
- É a estrutura usada por baixo dos panos em muitas bibliotecas de programação.

**Vantagens.**
- Inserção e remoção tendem a ser mais rápidas que na AVL, porque muita correção é feita só trocando cor, sem precisar rotacionar.
- Continua garantindo O(log n) para busca, inserção e remoção.
- É um ótimo equilíbrio entre custo de busca e custo de atualização, por isso é tão usada na prática.

**Desvantagens.**
- Como o balanceamento é menos rígido, a árvore pode ficar um pouco mais alta que a AVL, deixando as buscas levemente mais lentas.
- As regras de coloração tornam o código bem chato de implementar e de depurar.

**Exemplo ilustrado.** Uma Rubro-Negra simples, com a raiz preta e os filhos vermelhos (o que respeita todas as regras):

```
        (22) preto
        /        \
   (11) verm    (35) verm
```

Aqui a "altura negra" é a mesma para qualquer caminho, e não existem dois nós vermelhos em sequência, então a árvore está válida.

### Árvore N-ária

**Conceito.** Até aqui falamos só de árvores binárias, onde cada nó tem no máximo dois filhos. A árvore N-ária quebra essa limitação: cada nó pode ter N filhos, sendo N qualquer número. Não existe a regra de "esquerda e direita", e sim uma lista de filhos.

**Diferenças em relação à árvore binária.**
- Na binária, o limite é fixo em dois filhos por nó. Na N-ária, esse limite é maior (ou nem existe um limite fixo).
- A binaria organiza tudo em "menor à esquerda, maior à direita". A N-ária normalmente nao tem essa ordenação automática, ela serve mais pra representar hierarquias e relações de "pai e filhos".
- Por causa disso, a binária é mais voltada para busca ordenada, e a N-ária para modelar estruturas que têm muitos ramos.

**Aplicações práticas.**
- Sistema de arquivos: uma pasta pode conter várias subpastas e arquivos, então é uma hierarquia N-ária natural.
- O DOM de uma pagina HTML: cada elemento pode ter varios elementos filhos dentro dele.
- Organogramas de empresa, árvores genealógicas e menus de aplicativos, que também são hierarquias com vários ramos.

**Exemplo ilustrado.** Uma pasta com três itens dentro, e uma dessas pastas com mais arquivos:

```
            Documentos
           /     |      \
      Fotos   Trabalho   Musicas
              /     \
        prova.pdf  resumo.txt
```

---

## Parte 2 – Operações nas árvores

As rotações são o coração do balanceamento. A ideia geral é sempre a mesma: reorganizar alguns nós, mudando quem é pai de quem, sem nunca quebrar a ordem da árvore de busca (menor à esquerda, maior à direita). Existem quatro casos.

### Rotação simples à direita (caso esquerda-esquerda)

Acontece quando a árvore pende demais para a esquerda. A gente "puxa" o nó de cima para a direita.

Antes (o nó 50 está desbalanceado para a esquerda):

```
        50
       /
     35
    /
  20
```

Depois da rotação à direita em 50:

```
      35
     /  \
   20    50
```

### Rotação simples à esquerda (caso direita-direita)

É o espelho do caso anterior: a árvore pende demais para a direita, e a gente puxa o nó de cima para a esquerda.

Antes:

```
  20
    \
     45
       \
        60
```

Depois da rotação à esquerda em 20:

```
      45
     /  \
   20    60
```

### Rotação dupla esquerda-direita (LR)

Esse caso aparece quando o desbalanceamento está "torto": o problema vem da subárvore esquerda, mas inclinada para a direita. Uma rotação só não resolve, então a gente faz duas. Primeiro uma rotação à esquerda no filho, depois uma rotação à direita no nó desbalanceado.

Antes:

```
      60
     /
   40
     \
      50
```

Passo 1 – rotação à esquerda em 40:

```
      60
     /
   50
   /
 40
```

Passo 2 – rotação à direita em 60:

```
      50
     /  \
   40    60
```

### Rotação dupla direita-esquerda (RL)

É o espelho do caso LR. O problema vem da subárvore direita, mas inclinada para a esquerda. Faz-se primeiro uma rotação à direita no filho e depois uma rotação à esquerda no nó desbalanceado.

Antes:

```
  40
    \
     65
    /
  55
```

Passo 1 – rotação à direita em 65:

```
  40
    \
     55
       \
        65
```

Passo 2 – rotação à esquerda em 40:

```
      55
     /  \
   40    65
```

### Espelhamento / inversão da árvore

Inverter (ou espelhar) uma árvore é trocar de lugar a subárvore esquerda com a direita, em todos os nós. É uma operação clássica de exercício e tem usos reais quando se quer percorrer a árvore na ordem contrária.

Antes:

```
        40
       / \
      20   60
     / \   / \
    10 30 50 70
```

Depois do espelhamento (cada par esquerda/direita foi trocado):

```
        40
       / \
      60   20
     / \   / \
    70 50 30 10
```

Repare que a estrutura continua sendo uma árvore válida, só que "de trás para frente". Diferente das rotações, o espelhamento não tem a ver com balanceamento: ele muda a ordem dos dados de propósito.

---

## Parte 3 – Aplicação prática escolhida

**Aplicação escolhida: o índice de um banco de dados.**

Todo banco de dados relacional precisa achar registros rápido. Imagine uma tabela com milhões de clientes e a consulta "me traga o cliente de CPF X". Sem nenhuma estrutura de apoio, o banco teria que olhar registro por registro, o que seria lentíssimo. Por isso os bancos criam **índices**, e a estrutura por trás desses índices quase sempre é uma árvore.

**Qual árvore se encaixa melhor e por quê.** Para esse cenário, uma árvore balanceada (do tipo Rubro-Negra, ou a sua "prima" usada em disco, a B-Tree) é a melhor escolha. A justificativa, olhando os três pontos pedidos:

- **Desempenho:** um índice é consultado o tempo todo, mas também recebe inserções e remoções conforme os dados mudam. A Rubro-Negra garante O(log n) tanto na busca quanto na atualização, e gasta menos rotações que a AVL nas inserções. Isso evita que o indice fique lento quando muitos registros sao adicionados de uma vez.

- **Organização dos dados:** como é uma árvore de busca, os dados ficam ordenados pela chave. Isso ajuda não só na busca exata, mas também em consultas por faixa (por exemplo, "todos os clientes cadastrados entre duas datas"), que podem ser respondidas percorrendo a árvore em ordem.

- **Operações realizadas pelo sistema:** o banco faz muitas inserções, remoções e buscas misturadas. Uma AVL seria ótima se fosse quase só busca, mas como há bastante escrita, a Rubro-Negra dá um equilíbrio melhor entre o custo de manter a árvore organizada e o custo de consultá-la. Não é a toa que estruturas desse tipo são as usadas de verdade em bancos de dados e em coleções ordenadas de várias linguagens de programação.

---

## Parte 4 – Comparação entre as estruturas

| Estrutura | Nº Máximo de Filhos | Balanceamento | Complexidade de Busca | Complexidade de Inserção | Vantagem Principal | Desvantagem Principal | Exemplo de Aplicação |
|---|---|---|---|---|---|---|---|
| **AVL** | 2 | Sim, automático e rígido (fator de balanceamento sempre entre -1 e +1, corrigido por rotações) | O(log n) | O(log n) | Balanceamento rígido deixa a árvore baixa, então a busca é muito rápida | Faz mais rotações, então inserir e remover sai mais caro | Sistemas com muitas buscas e poucas alterações, como dicionários em memória |
| **Rubro-Negra** | 2 | Sim, automático e mais flexível (regras de cor, corrigidas por recoloração e rotações) | O(log n) | O(log n) | Bom equilíbrio entre busca e atualização, com menos rotações | A árvore pode ficar um pouco mais alta que a AVL, e o código é complexo | Índices de banco de dados e coleções ordenadas de bibliotecas (ex.: TreeMap em Java) |
| **N-ária** | N (vários por nó) | Não tem balanceamento automático por padrão | Depende da implementação (pode chegar a O(n) se não for ordenada) | Depende da implementação | Representa hierarquias com muitos ramos de forma natural | Sem ordenação/balanceamento garantidos, a busca pode ficar lenta | Sistema de arquivos, DOM de páginas HTML, organogramas |

---

## Conclusão

Estudando as três estruturas, dá pra perceber que não existe "a melhor árvore", e sim a mais adequada para cada situação. A AVL brilha quando o que mais importa é a velocidade de busca, porque o balanceamento rígido a mantém bem baixa. A Rubro-Negra abre mão de um pouco desse balanceamento para gastar menos esforço nas inserções e remoções, o que a torna a queridinha das aplicações reais, como índices de banco de dados. Já a N-ária resolve um problema totalmente diferente: representar hierarquias em que um elemento pode ter vários filhos, como pastas dentro de pastas. Entender essas diferencas ajuda a escolher a estrutura certa na hora de resolver um problema de verdade.

---

## Referências

_(Preencher com os materiais que o grupo usou de fato — livro da disciplina, slides, sites. Exemplo de formato:)_

- CORMEN, T. H. et al. *Algoritmos: Teoria e Prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.
- Material e slides da disciplina de Estrutura de Dados – UniCesumar.
