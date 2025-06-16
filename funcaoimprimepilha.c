#include <stdio.h>\
typedef struct {
int topo;


} pilha;

int main(){

}


void imprime (pilha*p){
    int i;
    if(p->topo==-1){
        return;
    }
    for (i=p->topo;i>0;i--){
        printf("%d",p->vet[i]);
    }

}