/*Faça uma função que remova um aluno dada a sua respectiva matricula.
Sua função deve reajustar os ponteiros ant e prox assim que remover o
elemento, não esqueça de verificar se a elemento que será removido
está em uma célula que é a primeira ou a última ou alguma célula do
meio da lista, para cada posição o ajuste dos ponteiros é diferente.*/
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

void inserirAlunoInicio(Nodo **lista, Aluno aluno) {
    Nodo *novoNodo = (Nodo *)malloc(sizeof(Nodo));
    novoNodo->aluno = aluno;
    novoNodo->ant = NULL;
    novoNodo->prox = *lista;

    if (*lista != NULL) {
        (*lista)->ant = novoNodo;
    }

    *lista = novoNodo;
}

void inserirAlunoFinal(Nodo **lista, Aluno aluno) {
    Nodo *novoNodo = (Nodo *)malloc(sizeof(Nodo));
    novoNodo->aluno = aluno;
    novoNodo->prox = NULL;

    if (*lista == NULL) {
        novoNodo->ant = NULL;
        *lista = novoNodo;
        return;
    }

    Nodo *ultimo = *lista;
    while (ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }

    ultimo->prox = novoNodo;
    novoNodo->ant = ultimo;
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
        printf("Aluno com matricula %d não encontrado!\n", matricula);
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

    printf("\nLista de Alunos:\n");
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

// Função para liberar a memória da lista
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

// Menu interativo
void menu() {
    printf("\nSistema de Gerenciamento de Alunos\n");
    printf("1. Inserir aluno no inicio\n");
    printf("2. Inserir aluno no final\n");
    printf("3. Remover aluno por matricula\n");
    printf("4. Listar todos os alunos\n");
    printf("5. Sair\n");
    printf("Escolha uma opcaoo: ");
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
                inserirAlunoInicio(&lista, criarAluno(matricula, nome, nota));
                break;
                
            case 2:
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                printf("Digite o nome: ");
                scanf(" %[^\n]", nome);
                printf("Digite a nota: ");
                scanf("%f", &nota);
                inserirAlunoFinal(&lista, criarAluno(matricula, nome, nota));
                break;
                
            case 3:
                printf("Digite a matricula do aluno a ser removido: ");
                scanf("%d", &matricula);
                removerAlunoPorMatricula(&lista, matricula);
                break;
                
            case 4:
                imprimirLista(lista);
                break;
                
            case 5:
                liberarLista(&lista);
                printf("Programa encerrado. Memoria liberada.\n");
                break;
                
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 5);

    return 0;
}

/*a lógica foi tentar localizar o aluno pelo número da matricula e remover ajusatando os ponteiros para os nodos próximos de sua posição para não modificar a estrutura*/