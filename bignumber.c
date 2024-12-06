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

//Adiciona um novo nó ao BigNumber no final
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

//Adiciona um novo no ao bignumber no começo
void add_digit_head(BigNumber number, int digit) {
    Node new_node = malloc(sizeof(Node));

    new_node->digit = digit;
    new_node->prev = NULL;
    new_node->next = number->begin;

    if (number->begin != NULL) {
        number->begin->prev = new_node;
    } else {
        number->end = new_node;
    }
    number->begin = new_node;
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
/* NÃO UTILIZADO
BigNumber char_bignumber(char *string) {
    int zero_to_the_left = 1;
    BigNumber number = create_bignumber();
    
    for (int i = 0; i < strlen(string); i++) {
        //Verifica se é um zero a esquerda
        if (zero_to_the_left == 1 && return_digit(string[i]) != -1) 
            zero_to_the_left = 0;

        if (zero_to_the_left == 0 && return_digit(string[i]) != -1) {
            add_digit(number, return_digit(string[i]));
        }
        else{
            printf("NOT AN INT");
            break;
        }
    }
    return number;
}
*/

//Le o bignumber
void read_bignumber(BigNumber number) {
    char character;

    while ((character = getchar()) != '\n')
        if (character >= '0' && character <= '9') 
            add_digit(number, return_digit(character));
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

//libera a memória do bignumber
void erase_bignumber(BigNumber number) {
    Node currentNode = number->begin;
    while (currentNode != NULL) {
        free(currentNode);
        currentNode = currentNode->next;
    }
}

BigNumber sum_bignumber(BigNumber number1, BigNumber number2) {
    Node currentNode1 = number1->end, currentNode2 = number2->end;
    int sum, sum_next_house = 0;

    while (currentNode1 != NULL || currentNode2 != NULL) {
        sum = currentNode1->digit + currentNode2->digit;

    }
}