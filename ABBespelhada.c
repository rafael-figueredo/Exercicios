#include <stdio.h>
#include <stlib.h>
typedef struct Arv{
    int info;
    struct Arv *esq,*dir;
}Tarv;
typedef Tarv*Parv;

Parv espelhada(Parv a){
    Parv b;
    if(a == NULLL) return(NULL);
    b = (Parv) malloc(sizeof(Tarv));
    b->info = a->info;
    b->esq = espelhada(a->dir);
    b->dir = espelhada(b->esq);
    return b;
}