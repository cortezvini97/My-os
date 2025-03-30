#include "stdio.h"
#include "system.h"

void int_to_str(int num, char *str) {
    int i = 0;
    int isNegative = 0;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    do {
        str[i++] = (num % 10) + '0';
        num = num / 10;
    } while (num != 0);

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    int index = 0;
    char temp[20];

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i+1] != '\0') {
            i++; 
            switch (format[i]) {
                case 'd': { 
                    int num = va_arg(args, int);
                    int_to_str(num, temp);
                    for (int j = 0; temp[j] != '\0'; j++) {
                        buffer[index++] = temp[j];
                    }
                    break;
                }
                case 's': { 
                    char *str = va_arg(args, char*);
                    for (int j = 0; str[j] != '\0'; j++) {
                        buffer[index++] = str[j];
                    }
                    break;
                }
                case 'c': { 
                    char ch = (char)va_arg(args, int);
                    buffer[index++] = ch;
                    break;
                }
                default:
                    buffer[index++] = format[i];
                    break;
            }
        } else {
            buffer[index++] = format[i];
        }
    }

    va_end(args);

    write(1, buffer, index);

    return index;
}