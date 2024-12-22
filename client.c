#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

int main() {
    BigNumber number1 = create_bignumber();
    BigNumber number2 = create_bignumber();

    printf("Insira o numero 1: ");
    read_bignumber(number1);
    printf("Insira o numero 2: ");
    read_bignumber(number2);

    BigNumber answer = sub_bignumber(number1, number2);
    print_bignumber(answer);

    erase_bignumber(number1);
    erase_bignumber(number2);
    erase_bignumber(answer);
    free(number1);
    free(number2);
    free(answer);
    return 0;
}
