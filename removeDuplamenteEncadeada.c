Plista2 removeD(Plista l, int v){
    Plista2 p;
    while (busca(l,v)!=NULL){
        if(p==l){
            l = l->prox;
            l->ant = NULL;
        }
        else {
            p->ant->prox = p->prox;
            if(p->prox != NULL)
                p->prox->ant = p->ant;
        }

    }
}