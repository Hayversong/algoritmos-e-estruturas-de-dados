# Algoritmos e Estruturas de Dados

Listas de exercícios e trabalhos das disciplinas de algoritmos do curso de Ciência da Computação. Cada pasta reúne uma lista ou trabalho, com o enunciado comentado no topo de cada arquivo.

| Pasta | Tema | Destaques |
|---|---|---|
| [01-recursao](01-recursao) | Recursão | Funções recursivas sobre números e vetores |
| [02-ponteiros](02-ponteiros) | Ponteiros | Aritmética de ponteiros, passagem por referência e alocação dinâmica |
| [03-pilhas](03-pilhas) | Pilhas | Operações novas sobre a pilha, como `push2` e `pop2` |
| [04-filas](04-filas) | Filas | Fila dinâmica (`FilaDin`) e simulação de fila de aviões |
| [05-listas-encadeadas](05-listas-encadeadas) | Lista dinâmica encadeada | Consultas por matrícula e por posição |
| [06-listas-duplamente-encadeadas](06-listas-duplamente-encadeadas) | Lista duplamente encadeada | Remoção com reajuste dos ponteiros `ant` e `prox` |
| [08-arvore-binaria](08-arvore-binaria) | Árvore binária de busca | Inserção, remoção e percurso em pré-ordem |
| [09-arvore-avl](09-arvore-avl) | Árvore AVL | Balanceamento por rotações |
| [trabalho-simulador-sistema-de-arquivos](trabalho-simulador-sistema-de-arquivos) | Árvores (trabalho) | Terminal que simula um sistema de arquivos em árvore, com comandos e caminhos |
| [ordenacao-externa](ordenacao-externa) | Ordenação externa (Python) | Merge sort externo: divide em blocos que cabem na memória, ordena e intercala com heap |

## Como compilar

Os exercícios em C foram feitos no Code::Blocks (MinGW, Windows). Os que usam um TAD compilam junto com a implementação dele:

```bash
gcc 05-listas-encadeadas/main.c 05-listas-encadeadas/ListaDinEncad.c -o lista
./lista
```

Alguns arquivos usam `windows.h` ou `gets` e compilam só no Windows ou em versões antigas do GCC.

A ordenação externa roda com Python 3:

```bash
cd ordenacao-externa
python mergesort.py
```

## Origem

Este repositório junta repositórios que antes eram separados (`Lista-1`, `lista-2` … `lista-9`, `trabalho-2` e `Estudo-algoritmos`). O histórico de commits de cada um foi preservado.
