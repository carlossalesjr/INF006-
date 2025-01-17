#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define STR_MAX 50

typedef struct
{
    char elementos[MAX][STR_MAX];
    int topo;
} Pilha;

int main()
{
    Pilha pilha;
    pilha.topo = 0;
    insercaoOrdenada(&pilha, "Walter");
    insercaoOrdenada(&pilha, "Daniele");
    insercaoOrdenada(&pilha, "Carla");
    insercaoOrdenada(&pilha, "Antonia");
    insercaoOrdenada(&pilha, "Bruno");
    for (int i = 0; i < pilha.topo; i++)
    {
        printf("%s\n", pilha.elementos[i]);
    }
    return 0;
}

int isEmpty(Pilha *pilha)
{
    return pilha->topo == 0;
}

int isFull(Pilha *pilha)
{
    return pilha->topo == MAX;
}

void insercaoOrdenada(Pilha *pilha, char *novoElemento)
{
    Pilha temp;
    temp.topo = 0;
    char elemento[STR_MAX];

    while (!isEmpty(pilha) && strcmp(pilha->elementos[pilha->topo - 1], novoElemento) > 0)
    {
        pop(pilha, elemento);
        push(&temp, elemento);
    }

    push(pilha, novoElemento);

    while (!isEmpty(&temp))
    {
        pop(&temp, elemento);
        push(pilha, elemento);
    }
}

void push(Pilha *pilha, char *elemento)
{
    if (isFull(pilha))
    {
        printf("pilha cheia.\n");
        return;
    }
    strcpy(pilha->elementos[pilha->topo++], elemento);
}

void pop(Pilha *pilha, char *elemento)
{
    if (isEmpty(pilha))
    {
        printf("pilha vazia.\n");
        return;
    }
    strcpy(elemento, pilha->elementos[--pilha->topo]);
}