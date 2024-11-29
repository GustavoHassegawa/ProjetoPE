#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

//Cria um numerão vazio
BigNumber create_bignumber() {
    BigNumber number = malloc(sizeof(BigNumber));

    number->begin = NULL;
    number->end = NULL;
    return number;
}

//Adiciona um novo nó ao BigNumber
void add_digit(BigNumber number, int digit) {
    Node new_node = malloc(sizeof(Node));

    new_node->digit = digit;
    new_node->prev = number->end;
    new_node->next = NULL;

    if (number->end != NULL) {
        number->end->next = new_node;
    } else {
        number->begin = new_node;
    }
    
    number->end = new_node;
}


