int iguais (PArv A, PArv B){
    if (A == NULL && B == NULL){
        return 1;
    }

    if(A == NULL || B == NULL){
        return 0;
    }

    if (A->info != B->info){
        return 0;
    }

    if (iguais(A->esq, B->esq) == 1){
        return (iguais(A->dir, B->dir)){
        }
    }

    else return 0;

}

return (A->info == B->info && iguais(A->esq,B->esq && iguais(A->dir, B->dir)));

