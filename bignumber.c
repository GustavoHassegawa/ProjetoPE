#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/*Retorna o dígito, se não for um número retorna '-1', visto que o sinal será
 *definido em outro momento, agora estou pensando apenas no valor do digito.*/
int return_digit(char character) {
    if (character >= '0' && character <= '9')
        return character - '0';
    else
        return -1;
}

//Cria um bignumber a partir de uma srting
BigNumber char_bignumber(char *string) {
    BigNumber number = create_bignumber();
    for (int i = 0; i < strlen(string); i++) {
        if (return_digit(string[i]) != -1) {
            add_digit(number, return_digit(string[i]));
        }
        else{
            printf("NOT AN INT");
            break;
        }
    }
    return number;
}

//Imprime um bignumber
void print_bignumber(BigNumber number) {
    Node currentNode = number->begin;
    while (currentNode != NULL) {
        printf("%d", currentNode->digit);
        currentNode = currentNode->next;
    }
    printf("\n");
}