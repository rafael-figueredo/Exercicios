void soma(matriz m1, matriz m2, int tam){
    int i , val col;
    pme p, q, novo, r;
    matriz result;
    for(i=0 ; i < ram ; i++){
        result[i] = NULL;
        p = m1[i]; q = m2[i];
        while(p != NULL || q != NULL){
            if(q == NULL || (p != NULL && p->col < q->col)){
                val = p->val;
                col = p->col;
                p=p->prox;
            }
            else if(p == NULL || 1->col < p->col){
                val = q->val;
                col = q->col;
                q = q->prox;
            }
            else{
                val = p->val + q->val;
                col = p->col;
                p = p->prox;
                q = q->prox;
            }
            if(val != 0){
                novo = malloc(sizeof(structno));
                novo->val = val;
                novo->col = col;
                novo->prox = NULL;
            }

            if(result [i] == NULL){|
                result[i] = novo;
                r = novo;
            }

            else{
                r->prox = novo;
                r = novo;
            }
        }
    }
    imrpime(result, tam);
    libera(result, tam);

}

void imprime (matriz m , it t){
    int i, j;
    pme p;
    for(i = 0 ; i < t ; I++){
        p = m[i];
        for(j = 0 ; j < t ; j++){
            if (p == NULL || p->col > j){
                printf("0");
            }

            else{
                printf("%d", p->val);
                p = p->prox;
            }
        }
        printf("\n");
    }
}

void libera (matriz m , int t){
    int i;
    ome p, q;
    for(i = 0 ; i < t ; i++){
        for(p = m[i] ; p != NULL ; ){
            q = p;
            p = p->prox;
            free(q);
        }
    m[i] = NULL;
    }    
}