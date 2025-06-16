#include <stdio.h>

typedef struct {
    char vet[MAX-PILHA];
    int topo;

}Tpilha



*Tpilha invertestring(Tpilha *p){
        int i;
        if(p->topo==-1){
            return;
        }
        for (i=p->topo;i>0;i--){
            printf("%d",p->vet[i]);
        }
    
    }
}