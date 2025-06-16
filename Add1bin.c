#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No*prox;
}Tno;

typedef Tno* Plista;

Plista PUSH (Plista lista, int N){
    Plista novo = (Plista)malloc(sizeof(Tno));
    if (lista == NULL){
        novo->prox = NULL;
        novo->info = N;
        return novo;
    }
    
    else{
        novo->prox = lista;
        novo->info = N;
        return novo;
    }
}

int POP (Plista lista){
    Plista p = lista;
    int N = p->info;
    lista = lista->prox;
    free(p);
    return N;
}



Plista Addrec(Plista lista, int carry){
    Plista pilha = NULL;
    if (lista == NULL){
        if(carry == 1){
            
        }
    }
    
}