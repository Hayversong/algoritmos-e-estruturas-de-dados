#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Protótipos

//Definição do tipo lista
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

struct fila {
    int info;
    struct fila *prox;
    struct fila *ant;
};

struct nodesc {
    struct fila *ini;
    struct fila *fim;
};
Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere início
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista não vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e único
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}

int insere_lista_inicio_circular(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if(*li == NULL){
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        no->prox = *li;
        Elem* aux = (*li)->ant;
        no->ant = aux;
        aux->prox = no;
        (*li)->ant = no;
        *li = no;
    }
    return 1;
}

int insere_lista_final_circular(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if(*li == NULL){ //lista vazia: insere início
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        no->prox = *li;
        Elem* aux = (*li)->ant;
        no->ant = aux;
        aux->prox = no;
        (*li)->ant = no;
    }
    return 1;
}
int remove_lista_final_circular(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem* ultimo = (*li)->ant;
    if(ultimo == *li){ // lista com um unico elemento
        *li = NULL;
    } else {
        Elem* aux = ultimo->ant;
        (*li)->ant = aux;
        aux->prox = *li;
    }
    free(ultimo);
    return 1;
}
int remove_lista_inicio_circular(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem* no = *li;
    if(no->prox == no){ // lista com um unico elemento
        *li = NULL;
    } else {
        Elem* ultimo = no -> ant;
        *li = no->prox;
        ultimo->prox = *li;
        (*li)->ant = ultimo;
    }

    free(no);
    return 1;
}
void imprime_lista_circular(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    do{
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }while(no != *li);
}

int inicializa_noDesc(noDesc *no){
    *no = (noDesc)malloc(sizeof(struct nodesc));
    //coloca a fila no estado de vazia
    if(!(*no)){
        return 0;
    }else{
        (*no)->ini = NULL;
        (*no)->fim = NULL;
        return 1;
    }
}

int enfileirar(noDesc *n, int elem) {
    if (n == NULL)
        return 0;
    struct fila *fila = (struct fila*) malloc(sizeof(struct fila));
    if (fila == NULL)
        return 0;
    fila->info = elem;
    fila->prox = NULL;
    fila->ant = NULL;
    if ((*n)->ini == NULL) { // fila vazia
        (*n)->ini = fila;
        (*n)->fim = fila;
    } else {
        fila->ant = (*n)->fim;
        (*n)->fim->prox = fila;
        (*n)->fim = fila;
    }
    return 1;
}

int desenfileirar(noDesc *n, int *elem) {
    if (n == NULL || *n == NULL)
        return 0;
    if ((*n)->ini == NULL) // fila vazia
        return 0;

    struct fila *remover = (*n)->ini;
    *elem = remover->info;

    if ((*n)->ini == (*n)->fim) { // só um elemento
        (*n)->ini = NULL;
        (*n)->fim = NULL;
    } else {
        (*n)->ini = remover->prox;
        (*n)->ini->ant = NULL;
    }

    free(remover);
    return 1;
}

void imprime_fila(noDesc n) {
    if (n == NULL)
        return;
    struct fila *aux = n->ini;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}
