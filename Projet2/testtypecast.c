#include <stdio.h>

int main(){
    int a = 8;
    int c = 78953453;
    char test[8];
    for(unsigned i = 8-1; i >= 0 && c; i--){
        test[i] = c % 10  +'0';
        c /= 10;
    }
    printf("%s",test);
    printf("\n");

    return 0;
}