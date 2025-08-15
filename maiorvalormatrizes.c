#include <stdio.h>
#define MAX_LINHA 100
typedef struct no *pme;
struct no{
    int col,val;
    pme prox;
}
typedef pme matriz[MAX_LINHA];

void submaiorvalor (matriz m, int lin){
    int i;
    pme p , maior, ant;
    for(i = 0 ; i < lin && m[i] != NULL ; i++);
    if(i==lin){
        printf("Nao ha valores");
    }
    pmaior = m[i];
    imaior = i;
    for ( ; i<lin ; i++){
        pant = NULL;
        for(p = m[i] ; p != NULL ; p = p->prox){
            if(p->val > pmaior){
                imaior = i;
                pmaior = p;
                pantmaior = pant;
            }
            pant = p;
        }
    }

    if(pontmaior == NULL){
        m[imaior] = pmaior->prox;
    }
    
    else{
        pant_maior->prox = pmaior->prox;
        free(pmaior);
    }
}