#include <stdio.h>
int main (){
    int V[50],Vi[50],n,i,s;

    scanf("%d",&n);
   if (n<=50 && n>1){
    for (i=0;i<n;i++){
        scanf("%d",&V[i]);

    }
    s=n-1;
    for (i=0;i<n;i++){
        Vi[i]=V[s-i];
        printf("%d ",Vi[i]);
    }
   }
   else
        printf("Erro");



return (0);
}
