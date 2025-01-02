#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

int main() {
    BigNumber number1, number2;
    BigNumber *vector = malloc(sizeof(BigNumber));
    int i = 0;
    int capacity = 1;
    char sinal;

    while(1) {
        number1 = create_bignumber();
        number2 = create_bignumber();

        read_bignumber(number1);
        if (number1->begin == NULL || number1->end == NULL) {
            erase_bignumber(number1);
            erase_bignumber(number2);
            break;
        }
        read_bignumber(number2);
        sinal = getchar();
        getchar();

        BigNumber answer = identify(number1, number2, sinal);
        
        i++;
        if (i >=capacity) {
            capacity *= 2;
            vector = realloc(vector, capacity * sizeof(BigNumber));
        }

        vector[i - 1] = answer;
        
        erase_bignumber(number1);
        erase_bignumber(number2);
    }

    for (int j = 0; j < i; j++) {
        print_bignumber(vector[j]);
        erase_bignumber(vector[j]);
    }

    free(vector);

    return 0;
}

