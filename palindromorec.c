#include <stdio.h>
#include <string.h>
int palindromo (char str[],int t,int ini){
    if (ini >= t){
        return 1;
    }
    
    else if(str[t] == str[ini]){
        return palindromo(str,t-1,ini+1);
    }
     return 0;
}





int main (){
    char str[100];
    int n,t,ini=0;
    fgets(str , 100 , stdin);
    t = strlen(str);
    n = palindromo(str,t-2, ini);
    printf("%d",n);


    return 0;
}