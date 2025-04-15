#include <stdio.h>
void contador(char str[]){
    int l=0,d=0,c=0,i;
    for (i=0 ; str[i]!= '\n' ; i++ ){
        if (str[i]>='A'&& str[i]<='Z'||str[i]>='a'&& str[i]<='z'){
            l++;

        }
        else

        if (str[i]>='0'&& str[i]<='9'){
            d++;
        }

        else {c++;}
}



        return ((l-d)*c);
}

int compara (char str[], char str2[]){
    int t1=0,t2=0,i;
    for (i=0 ; str[i]!= '\n' ; i++ ){
          t1++;
}
    for (i=0 ; str2[i]!= '\n' ; i++ ){
          t2++;
}
    if (t1!=t2){return 0;}

    else {
        for (i=0;i<t1;i++){
            if (str[i]!=str2[i]){
                return 0;
            }
        }
    }
    return 1;

}


int main(){
    int i1,i2,i3,*p1,*p2;
    char V1[500],V2[500];
    fgets(V1,500,stdin);
    fgets(V2,500,stdin);
    p1 = &V1;
    p2 = &V2;
    i1 = contador(V1);
    i2 = contador(V2);
    i3 = compara (V1,V2);


    printf("%d %d %d",i1,i2,i3);


return 0;
}
