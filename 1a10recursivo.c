#include <stdio.h>
int soma (int n){
    int valor;
    if (n==1){valor=1;}
    else {printf("%d ",n);
        return (soma(n-1));
    }
    return (valor);

}

int main (){
    int n;
    scanf("%d",&n);
    printf ("%d",soma(n));





return (0);
}
