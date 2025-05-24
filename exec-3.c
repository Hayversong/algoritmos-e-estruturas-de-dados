/*Faça um função que conte quantos alunos tem uma nota qualquer n1
igual, com o seguinte protótipo int conta_lista_nota(Lista* li, int n1). A
função deve utilizar apenas o ponteiro li passado como parâmetro, não
pode ser criado nenhum outro ponteiro auxiliar. Ao final além de informar
a quantidade alunos com a mesma nota, o ponteiro li deve estar
apontado para a primeira célula “cabeça” da lista.*/
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
    
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;
    
    novo->aluno = al;
    novo->ant = NULL;
    novo->prox = NULL;

    if (*lista == NULL) {
        *lista = novo;
        return 1;
    }

    Nodo *ant = NULL;
    Nodo *atual = *lista;
    
    while (atual != NULL && atual->aluno.matricula < al.matricula) {
        ant = atual;
        atual = atual->prox;
    }

    if (ant == NULL) {
        novo->prox = *lista;
        (*lista)->ant = novo;
        *lista = novo;
    }
    else if (atual == NULL) {
        ant->prox = novo;
        novo->ant = ant;
    }
    else {
        ant->prox = novo;
        novo->ant = ant;
        novo->prox = atual;
        atual->ant = novo;
    }
    
    return 1;
}

int conta_lista_nota(Nodo **li, float n1) {
    if (*li == NULL) {
        return 0;  // Lista vazia
    }

    int count = 0;
    Nodo *current = *li; 
    
    while (current != NULL) {
        if (current->aluno.nota == n1) {
            count++;
        }
        current = current->prox;
    }
    
    return count;
}

void removerAlunoPorMatricula(Nodo **lista, int matricula) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
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

void imprimirLista(Nodo *lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    printf("\nLista de Alunos (Ordenada por Matricula):\n");
    printf("-------------------------------------------------\n");
    printf("Matricula\tNome\t\t\tNota\n");
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
    printf("3. Contar alunos com nota especifica\n");
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
                printf("Digite a nota a ser buscada: ");
                scanf("%f", &nota);
                int qtd = conta_lista_nota(&lista, nota);
                printf("Quantidade de alunos com nota %.2f: %d\n", nota, qtd);
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