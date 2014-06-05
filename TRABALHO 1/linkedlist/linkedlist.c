/******************************************************** INCLUDES ********************************************************/ 

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************** FUNCOES ********************************************************/ 

/* Função que inicializa uma lista ligada, recebendo a função que devolve a chave e a função de comparação */

LinkedList createLinkedList(void* (*getKey)(void *), int (*compareFunction)(void *,void *)) {
    LinkedList newLinkedList = (LinkedList) malloc(sizeof (struct sLinkedList));
    newLinkedList->elems = NULL;
    newLinkedList->compareFunction = compareFunction;
    newLinkedList->getKey = getKey;
    newLinkedList->nrelems = 0;

    return newLinkedList;
}

/*Função que insere um novo elemento á cabeça de uma lista ligada*/

int pushLinkedList(LinkedList list, void *newData) {
    LinkedElem newElem = malloc(sizeof(struct sLinkedElem));

    newElem->data = newData;
    newElem->next = list->elems;
    list->elems = newElem;

    list->nrelems++;

    return 0;
}

/*Função que remove o elemento à cabeça de uma lista ligada*/

void* popLinkedList(LinkedList list) {
    if (list->nrelems == 0)
        return NULL;
    
    void *data = list->elems->data;
    LinkedElem newList = list->elems->next;
    free(list->elems);
    list->elems = newList;

    list->nrelems--;

    return data;
}

/*Função que insere um elemento de forma ordenada numa lista ligada*/

int ordInsertLinkedList(LinkedList list, void* newData) {
    LinkedElem *aux = &(list->elems);
    
    while (*aux != NULL && list->compareFunction((*aux)->data, newData) < 0) {
        aux = &((*aux)->next);
    }
   
    LinkedElem newElem;
    
    if (!(newElem = (LinkedElem) malloc(sizeof (struct sLinkedElem))))
        return -1;
    
    newElem->next = *aux;
    newElem->data = newData;
    *aux = newElem;

    list->nrelems++;

    return 0;
}

/* Função de procura numa lista ligada */

void* searchLinkedList(LinkedList list, int (*searchFunction)(void *, void *), void *params) {
    LinkedElem aux = list->elems;

    while (aux != NULL) {
        if (searchFunction(aux->data, params))
            return aux->data;
        aux = aux->next;
    }

    return NULL;
}

/* Função que remove um elemento de uma lista ligada*/

void* removeLinkedList(LinkedList list, void* key) {
    LinkedElem *elem = &(list->elems);
    LinkedElem aux;
    void* dataRes = NULL;

    while (*elem != NULL && ((list->compareFunction(list->getKey((*elem)->data),key))!=0)) {
        elem = &((*elem)->next);
    }

    if (*elem != NULL) {
        aux = *elem;
        dataRes = aux->data;
        *elem = (*elem)->next;
        free(aux);
        list->nrelems--;
    }

    return dataRes;

}

/* Função que limpa uma lista ligada */

int clearLinkedList(LinkedList list) {
    LinkedElem aux;

    while (list->elems != NULL) {
        aux = list->elems;
        list->elems = list->elems->next;
        free(aux);
    }

    free(list);

    return 0;
}


/* Função que aplica uma função a todos os nodos de uma lista ligada*/

void applyLikedList(LinkedList list, void (*function)(void *, void *), void *params) {
    LinkedElem aux = list->elems;

    while (aux != NULL) {
        function(aux->data, params);
        aux = aux->next;
    }
}


/* Função que insere um elemento no final de uma lista ligada */

int tailInsertLinkedList(LinkedList list, void *newData) {
    
    LinkedElem new = (LinkedElem) malloc (sizeof (struct sLinkedElem)) ;
    new->data = newData ;
    new->next = NULL ;

    if(list->elems == NULL)
        list->elems = new ;    
    else {
        LinkedElem l ;
        for(l = list->elems ; l->next != NULL; l = l->next) 
            ;
        l->next = new ;
    }

    list->nrelems ++ ;
    return 0 ;
}

/* Função que apaga todos os elementos de uma lista ligada */

int clearElemsLinkedList(LinkedList list) {

    LinkedElem aux;

    while (list->elems != NULL) {
        aux = list->elems;
        list->elems = list->elems->next;
        free(aux);
        list->nrelems -- ;
    }
    return 0 ;    
}