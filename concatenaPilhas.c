#include <stdio.h>
#include <stdlib.h>

typedef struct Tpilha{
    struct Tpilha *prox;
    int info;
} Tpilha;

typedef Tpilha* Ppilha;

Ppilha POP(Ppilha p, int *N){
    if (p == NULL){
        printf("pilha vazia");
        return NULL;
    }

    Ppilha temp = p;
    *N = p->info;
    p = p->prox;
    free(temp);
    return p;
}

Ppilha PUSH(ppilha, int N){
    Ppilha novo = (Ppilha)(malloc(sizeof(Tpilha)));
    novo->info = N; 
    novo->prox = ppilha;
    return novo;
}
