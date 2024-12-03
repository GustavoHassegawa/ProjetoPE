#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bignumber.h"

int main() {
    BigNumber number = create_bignumber();
    
    printf("Insira o numero: ");
    read_bignumber(number);
    
    print_bignumber(number);
    
    erase_bignumber(number);
    free(number);
    return 0;
}
