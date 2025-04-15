#include <stdio.h>
int multiplica (int a, int b){
    if (a == 0){
        return 0;
    }
    else return b + multiplica (a-1,b);

}


int main(){
    int b,a,c;
    scanf("%d",&a);
    scanf("%d",&b);
    c = multiplica (a,b);
    printf("%d",c);


return (0);
}
