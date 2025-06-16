Plitsa Pop (Plista ult){
    Plista p = ult->prox;
    ult->prox = p->prox;
    free(p);
}

Plista inserefila(Plista ult, int v){
    Plista novo = malloc(sizeof(Tlista));
    
}