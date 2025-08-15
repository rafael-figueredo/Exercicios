Parv pesquisaABB (Parv a, int v){
    if(a == NULL || a->info == v){
        return a;
    }

    if(v < a->info){
        return(pesquisaAB(a->esq, v));
    }

    return(pesquisaABB(a->dir, v));
}