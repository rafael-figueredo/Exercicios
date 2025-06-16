#include <stdio.h>
#include <stdlib.h>

typedef struct TipoItemD{
int info;
struct TipoItemD *prox, *ant;
}
TipoItemD;

typedef struct{
TipoItemD *inicio;
 } TipoListaCD;

void InsereOrdenado (TipoListaCD *lista, int info){
    TipoItemD *novo = malloc(sizeof(TipoItemD));
    novo->info = info;
    if(lista->inicio == NULL){
        novo->prox = novo;
        novo->ant = novo;
        lista->inicio = novo;
        return;
    }
    

    if(lista->inicio->info > info){
        TipoItemD *atras = lista->inicio->ant;
        novo->prox = lista->inicio;
        novo->ant = atras;
        lista->inicio->ant = novo;
        atras->prox = novo;
        lista->inicio = novo;
        return;
    }

    else{
        TipoItemD *frente = lista->inicio, *anterior;

        do{
            frente = frente->prox;
        } while(frente != lista->inicio && frente->info < info);

        anterior = frente->ant;
        novo->prox = frente;
        novo->ant = anterior;
        frente->ant = novo;
        anterior->prox = novo;
        return;

    }
}

TipoListaCD* MesclaLista(TipoListaCD* la, TipoListaCD *lb){
    TipoListaCD* resultado = malloc(sizeof(TipoListaCD));

    resultado->inicio = NULL;

    TipoItemD *p = la->inicio;


    if(la->inicio != NULL){    
    do {
        InsereOrdenado(resultado, p->info);
        p = p->prox;
    } while(p != la->inicio);
    }

    if(lb->inicio != NULL){
    p = lb->inicio;
    do{
        InsereOrdenado(resultado, p->info);
        p = p->prox;
    } while(p != lb->inicio);
    }

    return resultado;

}