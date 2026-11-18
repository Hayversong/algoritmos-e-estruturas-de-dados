#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
int main(){
    struct aluno al, a[4] = {{1,"Andre",9.5,7.8,8.5},
                             {2,"Ricardo",7.5,8.7,6.8},
                             {3,"Bianca",9.7,6.7,8.4},
                             {4,"Ana",5.7,6.1,7.4}};
    int escolha;
    printf("Deseja testar qual questao:\n4: Lista com comportamento circular\n5: Fila com o conceito de lista\n");
    scanf("%d",&escolha);
    switch(escolha){
        case 4:{
        /*
        4) Refaça as funções de inserir e remover no início e fim para que a lista
            comporte-se de forma circular. No fim, faça uma função que para
            percorrer a lista inteira utilizando o comportamento circular da mesma.
        */
        Lista* li = cria_lista();
        for(int i = 0; i < 4; i++){
            insere_lista_inicio_circular(li,a[i]);
        }
        printf("\n\n\nInseriu quatro elementos inicio\n\n\n");
        imprime_lista_circular(li);
        printf("\n\n\Inseriu elemento final\n\n\n");
        insere_lista_final_circular(li,a[0]);
        imprime_lista_circular(li);
        printf("\n\n\nRemoveu elemento final\n\n\n");
        remove_lista_final_circular(li);
        imprime_lista_circular(li);
        printf("\n\n\nRemoveu elemento inicio\n\n\n");
        remove_lista_inicio_circular(li);
        imprime_lista_circular(li);
        libera_lista(li);
        break;
        /*
        Lógica usada para inserir no início: o próximo do novo início
        aponta para o antigo início, o anterior do novo início aponta
        para o último, o próximo do último aponta para o novo início,
        e o anteror do antigo início aponta para o novo início também.
        Logica usada para inserir no final: o proximo do novo final
        aponta para o início, o anterior do novo final aponta para o
        antigo final, o próximo do antigo final aponta para o novo
        final, e o anterior do inicio aponta para o novo final.
        Lógica usada para remover no início:caso só tenha um elemento,
        libera a lista, se não, o próximo do último aponta pro novo inicio,
        o anterior do novo inicio aponta para o ultimo
        Lógica usada para remover no final: caso só tenha um elemento,
        libera a lista, se não, o proximo do anterior do último aponta
        pro início,o anterior do inicio aponta para o novo ultimo.
        Lógica usada pra imprimir: imprime os elementos até que chegue
        no primeiro elemento de novo.
        */
        }
        case 5:{
        /*
        5) Faça uma estrutura do tipo Fila utilizando o conceito de lista duplamente
            ou simplesmente encadeada, você pode escolher qual irá utilizar. É
            preciso criar as funções Enfileirar e Desenfileirar. Essas funções devem
            utilizar o conceito de nó descritor (nodesc), que é uma estrutura que
            controla onde está a célula inicial da lista e a célula final, a inserção e
            remoção na fila deve utilizar apenas os nós que estão na estrutura do nó
            descritor. Abaixo segue as duas estruturas que serão usadas, a função
            que inicializa o nó descritor e o cabeçalho das funções.
        */
        noDesc fila = NULL;
        inicializa_noDesc(&fila);

        for(int i = 0; i < 5; i++){
            enfileirar(&fila, i);
        }
        printf("\nFila:\n");
        imprime_fila(fila);
        printf("\nChamada da funcao desinfileirar:\n");
        int elemento;
        desenfileirar(&fila, &elemento);
        imprime_fila(fila);
        /*
        Lógica usada para enfileirar: caso a fila esteja vazia,
        o novo no se torna o inicio e o fim, caso ja tenhha
        elementos, o anterior do novo no aponta pro antigo final,
        o proximo do antigo final para para o novo no.
        Lógica usada para desinfileirar: caso só tenha um único
        elemento, o início e o fim são setados como NULL, caso
        ja tenha elementos, o inicio aponta para o proximo e o
        anterior desse proximo é setado como NULL
        */
        break;
        }
    }
    return 0;
}

