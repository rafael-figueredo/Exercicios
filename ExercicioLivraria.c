#include <stdio.h>
#include <stdlib.h>

typedef struct N{
    float D,*plivros;
    int qnt;
}
pessoa;

pessoa* preenche (int N){
    int j;
    float preco,D;
    pessoa *pessoas = (malloc(N*sizeof(pessoa)));
    for(int i=0 ; i<N ; i++){
        D = -1;
        j = -1;
        while(D<0){
            scanf("%f", &D);
        }
        pessoas[i].D = D;
        while(j<0||j>100){
            scanf("%d",&j);
        }
        pessoas[i].qnt = j;
        pessoas[i].plivros = malloc(j*sizeof(float));
        for (int k=0 ; k<j ; k++){
            preco = -1;
            while(preco<0){
                scanf("%f",&preco);
            }
            pessoas[i].plivros[k] = preco;
        }
    }
        return pessoas;
}

void imprime (pessoa *pessoas,int N){
    int qntdcomprados;
    for(int i=0 ; i<N ; i++){
        qntdcomprados=0;
        for(int j=0 ; j<pessoas[i].qnt ; j++){
            if (pessoas[i].D >= pessoas[i].plivros[j]){
                pessoas[i].D = (pessoas [i].D - pessoas[i].plivros[j]);
                qntdcomprados++;
            }
        }
        printf("%d ",qntdcomprados);
        printf("%.2f\n",pessoas[i].D);
        

    }
}


int main(){
    int N;
    while(N>100||N<1){
        scanf("%d" , &N);
    }
    pessoa *pessoas = preenche (N);
    imprime(pessoas,N);
    for (int i = 0; i < N; i++) {
        free(pessoas[i].plivros);
    }
    free(pessoas);

return 0;
}