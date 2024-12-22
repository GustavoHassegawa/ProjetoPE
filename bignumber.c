#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bignumber.h"

//Cria um numerão vazio
BigNumber create_bignumber() {
    BigNumber number = malloc(sizeof(BigNumber));

    number->size = 0;
    number->begin = NULL;
    number->end = NULL;
    return number;
}

//Adiciona um novo nó ao BigNumber no final
void add_digit_end(BigNumber number, int digit) {
    Node new_node = malloc(sizeof(Node));

    new_node->digit = digit;
    new_node->prev = number->end;
    new_node->next = NULL;

    if (number->end != NULL) {
        number->end->next = new_node;
    } else {
        number->begin = new_node;
    }
    number->size++;
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
    number->size++;
    number->begin = new_node;
}

//Apaga o digito do início do bignumber
void erase_digit_head(BigNumber number) {
    Node temp = number->begin->next;
    free(number->begin);
    number->begin = temp; 
    number->begin->prev = NULL;
}

//Apaga o digito do final do bignumber
void erase_digit_end(BigNumber number) {
    Node temp = number->end->prev;
    free(number->begin);
    number->end = temp;
    number->end->next = NULL;
    number->size--;
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
            add_digit_end(number, return_digit(character));
}

//Imprime um bignumber
void print_bignumber(BigNumber number) {
    Node currentNode = number->begin;
    if (number->negative == true)
        printf("-");
    while (currentNode != NULL) {
        printf("%d", currentNode->digit);
        currentNode = currentNode->next;
    }
    printf("\n");
}

//libera a memória do bignumber
void erase_bignumber(BigNumber number) {
    Node currentNode = number->begin;
    Node temp;
    while (currentNode != NULL) {
        temp = currentNode->next;
        free(currentNode);
        currentNode = temp;
    }
}

void delete_left_zeros(BigNumber number) {
    Node currentNode = number->begin;
    while (currentNode != number->end) {
        if (currentNode->digit != 0)
            break;
        currentNode = currentNode->next;
        erase_digit_head(number);
    }
}

/*função modulariza todos os nós do bignumber para que os digitos sejam somente 
 *de 0 a 9*/
void node_modularizer(BigNumber number) {
    Node currentNode = number->end;

    delete_left_zeros(number);
    while (currentNode != NULL) {

        if (currentNode->digit < 0) {
            if (currentNode->prev == NULL) {
                currentNode->digit *= -1;
                number->negative = true;
            } else {    
                currentNode->prev->digit--;
                currentNode->digit += 10;
            }
        }

        if (currentNode->digit > 9) {
            int addNext;

            addNext = currentNode->digit/10;
            currentNode->digit %= 10;

            if (currentNode->prev == NULL)
                add_digit_head(number, 0);

            currentNode->prev->digit += addNext;
        }

        currentNode = currentNode->prev;
    }
    delete_left_zeros(number);
}

//Faz a soma de um bignumber por um outro bignumber.
BigNumber sum_bignumber(BigNumber number1, BigNumber number2) {
    Node currentNode1 = number1->end, currentNode2 = number2->end;
    short int sum;
    BigNumber answer = create_bignumber();

    while (currentNode1 != NULL || currentNode2 != NULL) {

        if (currentNode1 == NULL && currentNode2 != NULL) {
            sum = currentNode2->digit;
            currentNode2 = currentNode2->prev;

        } else if (currentNode1!= NULL && currentNode2 == NULL) {
            sum = currentNode1->digit;
            currentNode1 = currentNode1->prev;

        } else {
            sum = currentNode1->digit + currentNode2->digit;
            currentNode1 = currentNode1->prev;
            currentNode2 = currentNode2->prev;
        }
        add_digit_head(answer, sum);
    }        
    node_modularizer(answer);

    return answer;
}

BigNumber sub_bignumber(BigNumber minuend, BigNumber subtrahend) {
    Node currentNodeMinuend = minuend->end, currentNodeSubtra = subtrahend->end;
    short int sub;
    BigNumber answer = create_bignumber();

    if (subtrahend->size > minuend->size) {
        answer = sub_bignumber(subtrahend, minuend);
        answer->negative = true;
        return answer;
    }

    while (currentNodeMinuend != NULL || currentNodeSubtra != NULL) {

        if (currentNodeMinuend == NULL && currentNodeSubtra != NULL) {
            sub = -currentNodeSubtra->digit;
            currentNodeSubtra = currentNodeSubtra->prev;

        } else if (currentNodeMinuend != NULL && currentNodeSubtra == NULL) {
            sub = currentNodeMinuend->digit;
            currentNodeMinuend = currentNodeMinuend->prev;

        } else {
            sub = currentNodeMinuend->digit - currentNodeSubtra->digit;
            currentNodeSubtra = currentNodeSubtra->prev;
            currentNodeMinuend = currentNodeMinuend->prev;
        }
        add_digit_head(answer, sub);
    }
    node_modularizer(answer);
    return answer;
}
