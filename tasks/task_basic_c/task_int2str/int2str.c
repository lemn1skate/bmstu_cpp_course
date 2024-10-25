#include <stdlib.h>
#include "int2str.h"

char* int2str(int num) {
    int size = 0;
    int znak = 0;

    long long number = num;
    
    if (number<0){
        number = -number;
        size++;
        znak = 1;
    }
    long long v = number;
    while (v>0){
        size++;
        v/=10;
    }
    
    char* stroka = malloc((size+1)*(sizeof(char)));

    if (number == 0 ){
        return "0";
    }

    if (znak==1){
        stroka[0]='-';
    }
    
    stroka[size] = '\0';

    for (int i=size-1; i>=znak; i--){
        stroka[i]=(number%10)+'0';
        number/=10;
    }
    return stroka;
    }
