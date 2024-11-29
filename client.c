#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bignumber.h"

int main() {
    char *bignumberString;
    int tamanho = 0;
    BigNumber number;

    printf("Tamanho do numero: ");
    scanf("%d", &tamanho);
    getchar();
    bignumberString = malloc((tamanho + 1) * sizeof(char));
    
    printf("Insira o numero: ");
    fgets(bignumberString, tamanho + 1, stdin);
    number = char_bignumber(bignumberString);
    
    print_bignumber(number);

    erase_bignumber(number);
    free(number);
    free(bignumberString);
    return 0;
}
