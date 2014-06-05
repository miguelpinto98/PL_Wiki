#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

/******************************************************** ESTRUTURA ********************************************************/

/* Elementos da Lista Ligada */
typedef struct sLinkedElem{
    void* data;
    struct sLinkedElem *next;
}*LinkedElem;

/* Lista Ligada com elementos e funções */
typedef struct sLinkedList{
    LinkedElem elems;
    void* (*getKey)(void*);
    int (*compareFunction)(void* ,void*);
    int nrelems;
}*LinkedList;

/******************************************************** FUNCOES ********************************************************/

/* Função que inicializa uma lista ligada, recebendo a função que devolve a chave e a função de comparação */
LinkedList createLinkedList(void* (*getKey)(void *), int (*compareFunction)(void *,void *));

/*Função que insere um novo elemento á cabeça de uma lista ligada*/
int pushLinkedList(LinkedList list, void *newData);

/*Função que remove o elemento à cabeça de uma lista ligada*/
void* popLinkedList(LinkedList list);

/*Função que insere um elemento de forma ordenada numa lista ligada*/
int ordInsertLinkedList(LinkedList list, void* newData);

/* Função de procura numa lista ligada */
void* searchLinkedList(LinkedList list, int (*searchFunction)(void *, void *), void *params);

/* Função que remove um elemento de uma lista ligada*/
void* removeLinkedList(LinkedList list, void* key);

/* Função que limpa uma lista ligada */
int clearLinkedList(LinkedList list);

/* Função que aplica uma função a todos os nodos de uma lista ligada*/
void applyLikedList(LinkedList list, void (*function)(void *, void *), void *params);

/* Função que insere um elemento no final de uma lista ligada */
int tailInsertLinkedList(LinkedList list, void *newData);

/* Função que apaga todos os elementos de uma lista ligada */
int clearElemsLinkedList(LinkedList list);

#endif