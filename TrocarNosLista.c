#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista*prox;
}Tlista;

typedef Tlista* Plista;

int TrocaNo(Plista lista, int a, int b){
    Plista antA, auxA, antB, auxB, temp;
    auxA = lista, antA = NULL;
    while (auxA != NULL && auxA->info != a){
        antA = auxA;
        auxA = auxA->prox;
    }

    auxB = lista, antB = NULL;
    while (auxB != NULL && auxB->info != b){
        antB = auxB;
        auxB = auxB->prox;
    }

    if (auxA == NULL || auxB == NULL){
        return 0;
    }

    if (antA != NULL){
        antA->prox = auxB;
    }

    if(antB != NULL){
        antB->prox = auxA;
    }

    temp = auxB->prox;
    auxB->prox = auxA->prox;
    auxA->prox = temp;
    return 1;
}