#include <stdio.h>
void imprimepilha(Ppilha pilha){
    Ppilha 
    while(prox!=NULL){

    }
}
void freepilha(Ppilha pilha){
    Ppilha p;
    while (pilha!=NULL){
        p = pilha;
        pilha = pilha->prox;
        free(p);
    }
}
Ppilha imprimerecursiva(Ppilha pilha){
    if (pilha==NULL){
        return 
        
    }
    else {
        printf("%d",pilha->info);
        return imprimerecursiva(pilha->prox);
    }
}
void removerec(Ppilha pilha){
    if (pilha == NULL){
        return;
    }

    

}