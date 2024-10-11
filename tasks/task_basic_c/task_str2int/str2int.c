#include <stdio.h>

int str2int(const char *str) {
    int a = 0;
    int b = 1;
    
    // Пропускаем пробелы
    while (*str == ' ') {
        str++;
    }
    // Проверка на знак
    if (*str == '-') {
        b = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    // Преобразование символов в число
    while (*str >= '0' && *str <= '9') {
        a = a * 10 + (*str - '0');
        str++;
    }

    return b * a;
}
    return 0;
