#include <stdio.h>
void imprimelista (lista*l){
    while (l!=NULL){
        printf("%d",l->info);
    }
}

void liberalista (lista*l){
    lista *aux;
    while (l!=NULL){
        aux=l
        l=l->prox;

    }
}

void liberarec (lista*l){
    if (l==NULL){
        return;
    }
    liberarec(l->prox);
    free(l);
}

lista* removerec (lista*l,int N){
    if(l==NULL){
        return NULL;
    }
    if(l->info == N){
        return l;
    }
    else {
        removerec(l->prox)
    }}

int comparalistas (lista*l1,lista*l2){
    int i=1;
    lista*aux1==l1;
    lista*aux2==l2;
    while(aux1==aux2 && aux1!=NULL){
        aux1=aux1->prox;
        aux2=aux2->prox;
    }

}

plista removeval (plista l,int N){
    plista p=l,ant=NULL;
    while (p!=NULL){
        if(p->info==N){
            if(ant==NULL){
                l=l->prox;
                free(p);
                p=l;
            }
            else{
            ant->prox = p->prox;
            free(p);
            p=ant->prox;
            }
        }
        else {
            ant=p;
            p=p->prox;
        }
    }
    return l;
}