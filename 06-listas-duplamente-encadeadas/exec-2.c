/*Faça uma função que insira um novo elemento na lista de forma
ordenada. Utilize a função insere_lista_ordenada da lista encadeada
como base para criar essa função*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int matricula;
    char nome[50];
    float nota;
} Aluno;

typedef struct nodo {
    Aluno aluno;
    struct nodo *ant;
    struct nodo *prox;
} Nodo;

Aluno criarAluno(int matricula, const char *nome, float nota) {
    Aluno novo;
    novo.matricula = matricula;
    strncpy(novo.nome, nome, sizeof(novo.nome));
    novo.nota = nota;
    return novo;
}

int insere_lista_ordenada(Nodo **lista, Aluno al) {
    if (lista == NULL)
        return 0;
    
    // Cria novo nó
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;
    
    novo->aluno = al;
    novo->ant = NULL;
    novo->prox = NULL;

    // Caso 1: Lista vazia
    if (*lista == NULL) {
        *lista = novo;
        return 1;
    }

    Nodo *ant = NULL;
    Nodo *atual = *lista;
    
    // Percorre até encontrar a posição correta
    while (atual != NULL && atual->aluno.matricula < al.matricula) {
        ant = atual;
        atual = atual->prox;
    }

    // Caso 2: Inserir no início
    if (ant == NULL) {
        novo->prox = *lista;
        (*lista)->ant = novo;
        *lista = novo;
    }
    // Caso 3: Inserir no final
    else if (atual == NULL) {
        ant->prox = novo;
        novo->ant = ant;
    }
    // Caso 4: Inserir no meio
    else {
        ant->prox = novo;
        novo->ant = ant;
        novo->prox = atual;
        atual->ant = novo;
    }
    
    return 1;
}

void removerAlunoPorMatricula(Nodo **lista, int matricula) {
    if (*lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    Nodo *atual = *lista;
    
    while (atual != NULL && atual->aluno.matricula != matricula) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Aluno com matricula %d nao encontrado!\n", matricula);
        return;
    }
    
    if (atual->ant == NULL) {
        *lista = atual->prox;
        if (*lista != NULL) {
            (*lista)->ant = NULL;
        }
    } 
    else if (atual->prox == NULL) {
        atual->ant->prox = NULL;
    }
    else {
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }
    
    free(atual);
    printf("Aluno com matricula %d removido com sucesso!\n", matricula);
}

void buscarAluno(Nodo *lista, int matricula) {
    Nodo *atual = lista;
    
    while (atual != NULL) {
        if (atual->aluno.matricula == matricula) {
            printf("\nAluno encontrado:\n");
            printf("Matrícula: %d\n", atual->aluno.matricula);
            printf("Nome: %s\n", atual->aluno.nome);
            printf("Nota: %.2f\n", atual->aluno.nota);
            return;
        }
        atual = atual->prox;
    }
    
    printf("Aluno com matricula %d nao encontrado!\n", matricula);
}

void imprimirLista(Nodo *lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    printf("\nLista de Alunos (Ordenada por Matrícula):\n");
    printf("-------------------------------------------------\n");
    printf("Matrícula\tNome\t\t\tNota\n");
    printf("-------------------------------------------------\n");

    Nodo *atual = lista;
    while (atual != NULL) {
        printf("%d\t\t%s\t\t%.2f\n", 
               atual->aluno.matricula, 
               atual->aluno.nome, 
               atual->aluno.nota);
        atual = atual->prox;
    }
    printf("-------------------------------------------------\n");
}

void liberarLista(Nodo **lista) {
    Nodo *atual = *lista;
    Nodo *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    *lista = NULL;
}

void menu() {
    printf("\nSistema de Gerenciamento de Alunos\n");
    printf("1. Inserir aluno (ordenado por matricula)\n");
    printf("2. Remover aluno por matricula\n");
    printf("3. Buscar aluno por matricula\n");
    printf("4. Listar todos os alunos\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Nodo *lista = NULL;
    int opcao, matricula;
    char nome[50];
    float nota;

    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                printf("Digite o nome: ");
                scanf(" %[^\n]", nome);
                printf("Digite a nota: ");
                scanf("%f", &nota);
                if (insere_lista_ordenada(&lista, criarAluno(matricula, nome, nota))) {
                    printf("Aluno inserido com sucesso!\n");
                } else {
                    printf("Erro ao inserir aluno!\n");
                }
                break;
                
            case 2:
                printf("Digite a matricula do aluno a ser removido: ");
                scanf("%d", &matricula);
                removerAlunoPorMatricula(&lista, matricula);
                break;
                
            case 3:
                printf("Digite a matricula do aluno a ser buscado: ");
                scanf("%d", &matricula);
                buscarAluno(lista, matricula);
                break;
                
            case 4:
                imprimirLista(lista);
                break;
                
            case 5:
                liberarLista(&lista);
                printf("Programa encerrado. Memoria liberada.\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}

/*segui a estrutura do código anterior e tentei implementar a função fazendo poucas alterações como ajustar o ponteiro sempre que um novo nodo for inserido*/