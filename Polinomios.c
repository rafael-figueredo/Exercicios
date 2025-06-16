#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int exp, coef;
    struct No *ant;
    struct No *prox;
}Tlista;

typedef Tlista* Plista;


Plista InserePolinomios(){
    int coef, exp;
    Plista poli = NULL, novo, p;
    for (int i = 0 ; i < 5 ; i++){
        scanf("%d", &exp);
        scanf("%d", &coef);
        novo = (Plista)malloc(sizeof(Tlista));
        novo->exp = exp;
        novo->coef = coef;
        p = poli;
        if (poli == NULL){
            novo->prox = NULL;
            novo->ant = NULL;
            poli = novo;
        }
        
        else{
            while(novo->exp <= p->exp && p->prox != NULL){
                p = p->prox;
            }

            if(p->exp == novo->exp){
                p->coef += novo->coef;
                free(novo);
            }

            -else if (p->exp > exp) {
            // Inserção antes de p
            novo->prox = p;
            novo->ant = p->ant;
            if (p->ant) p->ant->prox = novo;
            p->ant = novo;

            // Se p era o primeiro, atualiza poli
            if (p == poli) poli = novo;
        }
        else {
            // Inserção após p (no final)
            p->prox = novo;
            novo->ant = p;
        }
    }

    return poli;
}
}


void ImprimePolinomio(Plista poli) {
    Plista p = poli;
    while (p != NULL) {
        printf("%dx^%d", p->coef, p->exp);
        if (p->prox) printf(" + ");
        p = p->prox;
    }
    printf("\n");
}

