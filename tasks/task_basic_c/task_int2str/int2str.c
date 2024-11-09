#include <stdlib.h>
#include "int2str.h"

char* int2str(int num) {
    int size = 0;
    int symbol = 0;

    if (num<0){
        num = -num;
        size++;
        symbol = 1;
    }

    unsigned int number = num;
    
    unsigned int  v = number;

    while (v>0){
        size++;
        v/=10;
    }

    char * str = malloc((size+1)*(sizeof(char)));

    if (number == 0){
        return "0";
    }

    if (symbol == 1){
        str[0]='-';
    }

    str[size] = '\0';

    for (int i=size-1; i>=symbol; i--){
        str[i]=(number%10)+'0';
        number/=10;
    }

    return str;
}
