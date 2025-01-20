#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bignumber.h"

//Cria um numerão vazio
BigNumber create_bignumber() {
    BigNumber number = malloc(sizeof(BigNumber));

    number->size = 0;
    number->begin = NULL;
    number->end = NULL;
    number->negative = false;
    return number;
}

BigNumber create_bignumber_zero() {
    BigNumber number = malloc(sizeof(BigNumber));
    Node node = malloc(sizeof(node));

    node->digit = 0;
    node->next = NULL;
    node->prev = NULL;

    number->size = 1;
    number->begin = node;
    number->end = node;
    number->negative = false;
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
    number->size--;
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
BigNumber char_bignumber(char *string) {
    int zero_to_the_left = 1;
    BigNumber number = create_bignumber();
    
    if (string[0] == '-') {
        number->negative = true;
    }

    for (int i = 0; i < strlen(string); i++) {
        
        //Verifica se é um zero a esquerda
        if (zero_to_the_left == 1 && return_digit(string[i]) != -1) 
            zero_to_the_left = 0;

        if (zero_to_the_left == 0 && return_digit(string[i]) != -1) {
            add_digit_end(number, return_digit(string[i]));
        }
    }
    return number;
}

//Le o bignumber
void read_bignumber(BigNumber number) {
    char character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if(character == '-')
            number->negative = true;
        if (character >= '0' && character <= '9') 
            add_digit_end(number, return_digit(character));
    }
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
    free(number);
}

//Elimina os zeros a esquerda.
void delete_left_zeros(BigNumber number) {
    Node currentNode = number->begin;
    while (currentNode != number->end) {
        if (currentNode->digit != 0)
            break;
        currentNode = currentNode->next;
        erase_digit_head(number);
    }
}

int is_equal(BigNumber a, BigNumber b) {
    Node currentNodeA = a->begin;
    Node currentNodeB = b->begin;
    
    if (a->negative != b->negative)
        return 0;

    if (a->size != b->size) 
        return 0;
    
    while (currentNodeA != NULL) {
        if (currentNodeA->digit != currentNodeB->digit)
            return 0;
        currentNodeA = currentNodeA->next;
        currentNodeB = currentNodeB->next;
    }
    return 1;
}

//Retorna se o número a é maior que o b
int is_bigger(BigNumber a, BigNumber b) {
    Node currentNodeA = a->begin;
    Node currentNodeB = b->begin;

    if (a->negative == true && b->negative == false)
        return 0;
    if (a->negative == false && b->negative == true)
        return 1;

    if (a->negative == true && b->negative == true) {
        if (a->size > b->size)
            return 0;

        if (a->size < b->size)
            return 1;

        if (a->size == b->size) {
            while(currentNodeA != NULL) {
                if (currentNodeA->digit > currentNodeB->digit) 
                    return 0;
                if (currentNodeA->digit < currentNodeB->digit)
                    return 1;
                currentNodeA = currentNodeA->next;
                currentNodeB = currentNodeB->next;
            }
        }
    }
    else {
        if (a->size > b->size)
            return 1;

        if (a->size < b->size)
            return 0;

        if (a->size == b->size) {
            while(currentNodeA != NULL) {
                if (currentNodeA->digit > currentNodeB->digit) 
                    return 1;
                if (currentNodeA->digit < currentNodeB->digit)
                    return 0;
                currentNodeA = currentNodeA->next;
                currentNodeB = currentNodeB->next;
            }
        }
    }

    return 0;
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
    BigNumber answer;
    short int sum;

    if (number1->negative == true && number2->negative == false) {
        number1->negative = false;
        return sub_bignumber(number2, number1);
    }

    else if (number1->negative == false && number2->negative == true) {
        number2->negative = false;
        return sub_bignumber(number1, number2);
        
    } else {
        answer = create_bignumber();

        if (number1->negative == true) 
            answer->negative = true;

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
}

/*Faz a soma de um bignumber por um outro bignumber e armazena o valor no 
 *segundo termo. Por enquanto implementado somente para positivos*/
void sum_bignumber_void(BigNumber number, BigNumber out) {
    Node currentNode1 = number->end, currentNode2 = out->end;

    while (currentNode1 != NULL || currentNode2 != NULL) {
        if (currentNode1 != NULL && currentNode2 == NULL) {
            add_digit_head(out, currentNode1->digit);
            currentNode1 = currentNode1->prev;

        } else if (currentNode1 == NULL && currentNode2 != NULL) {
            break;
        }
        else {
            currentNode2->digit += currentNode1->digit;
            currentNode1 = currentNode1->prev;
            currentNode2 = currentNode2->prev;
        }
    }
    node_modularizer(out);
}

//Faz a subtração de um bignumber minuendo por um bignumber subtraendo
BigNumber sub_bignumber(BigNumber minuend, BigNumber subtrahend) {
    Node currentNodeMinuend = minuend->end, currentNodeSubtra = subtrahend->end;
    short int sub;
    BigNumber answer;

    if (is_bigger(subtrahend, minuend)) {
        answer = sub_bignumber(subtrahend, minuend);
        answer->negative = true;
        return answer;
    }

    if (minuend->negative == true && subtrahend->negative == false) {
        minuend->negative = false;
        answer = sum_bignumber(minuend, subtrahend);
        answer->negative = true;
        return answer;
    }

    if (minuend->negative == true && subtrahend->negative == true) {
        minuend->negative = false;
        subtrahend->negative = false;
        return sub_bignumber(subtrahend, minuend);
    } 
    
    if (minuend->negative == false && subtrahend->negative == true) {
        subtrahend->negative = false;
        return sum_bignumber(minuend, subtrahend);
    }

    answer = create_bignumber();
    
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

/*Faz a subtração de um bignumber por um outro bignumber e armazena o valor no 
 *segundo termo. Por enquanto implementado somente para positivos e quando out 
 *é maior que o number (out - number)*/
void sub_bignumber_void(BigNumber number, BigNumber out) {
    Node currentNode1 = number->end, currentNode2 = out->end;

    while (currentNode1 != NULL || currentNode2 != NULL) {
        if (currentNode1 == NULL && currentNode2 != NULL) {
            break;
        }
        else {
            currentNode2->digit -= currentNode1->digit;
            currentNode1 = currentNode1->prev;
            currentNode2 = currentNode2->prev;
        }
    }
    node_modularizer(out);
}

// Faz a multiplicação de um BigNumber por outro.
BigNumber multi_bignumber(BigNumber multiplicand, BigNumber multiplier) {
    Node currentNodeMultiplicand = multiplicand->end;
    Node currentNodeMultiplier = multiplier->end;
    int zerosToAdd = 0, digitMultiplier, digitTemp;
    BigNumber answer = create_bignumber_zero(), temp;

    if (multiplicand->size == 1 && currentNodeMultiplicand->digit == 0) 
        return answer;
    
    if (multiplier->size == 1 && currentNodeMultiplier->digit == 0) 
        return answer;
    
    while (currentNodeMultiplier != NULL) {
        temp = create_bignumber();
        digitMultiplier = currentNodeMultiplier->digit;

        while (currentNodeMultiplicand != NULL) {
            digitTemp = digitMultiplier * currentNodeMultiplicand->digit;
            add_digit_head(temp, digitTemp);
            currentNodeMultiplicand = currentNodeMultiplicand->prev;
        }

        for (int i = 0; i < zerosToAdd; i++)
            add_digit_end(temp, 0);
        
        sum_bignumber_void(temp, answer);
        erase_bignumber(temp);

        zerosToAdd++;
        currentNodeMultiplier = currentNodeMultiplier->prev;
        currentNodeMultiplicand = multiplicand->end;
    }

    if (multiplicand->negative == true && multiplier->negative == true) 
        answer->negative = false;
    else if(multiplicand->negative == false && multiplier->negative == false)
        answer->negative = false;
    else
        answer->negative = true;

    return answer;
}

BigNumber div_bignumber(BigNumber dividend, BigNumber divisor) {
    BigNumber quotient = create_bignumber(), temp;
    Node currentNodeDividend;
    bool first = false;
    int digitQuotient = 0;

    if (divisor->negative != dividend->negative)
        quotient->negative = true;

    dividend->negative = false;
    divisor->negative = false;  


    if (is_bigger(divisor, dividend)) {
        add_digit_end(quotient, 0);
        quotient->negative = false;
        return quotient;
    }        

    if (is_equal(divisor, dividend)) {
        add_digit_end(quotient, 1);
        return quotient;
    }

    temp = create_bignumber();
    currentNodeDividend = dividend->begin;

    while (currentNodeDividend != NULL) {
        add_digit_end(temp, currentNodeDividend->digit);
        currentNodeDividend = currentNodeDividend->next;

        if (first == true) {
            while (!is_bigger(temp, divisor) && currentNodeDividend != NULL) {
                add_digit_end(quotient, digitQuotient);
                add_digit_end(temp, currentNodeDividend->digit);
                currentNodeDividend = currentNodeDividend->next;
            }
            if (currentNodeDividend == NULL && !is_bigger(temp, divisor)) {
                add_digit_end(quotient, 0);
            }
        }

        if (is_bigger(temp, divisor)) {
            first = true;
            while (is_bigger(temp, divisor) || is_equal(temp, divisor)) {
                sub_bignumber_void(divisor, temp);
                digitQuotient++;
            }
            add_digit_end(quotient, digitQuotient);
            digitQuotient = 0;
        }
    }

    erase_bignumber(temp);
    return quotient;
}

BigNumber identify(BigNumber numberA, BigNumber numberB, char operation) {
    if (operation == '+')
        return sum_bignumber(numberA, numberB);
    else if (operation == '-')
        return sub_bignumber(numberA, numberB);
    else if (operation == '*')
        return multi_bignumber(numberA, numberB);
    else if (operation == '/')
        return div_bignumber(numberA, numberB);
    else {
        printf("NÃO IMPLEMENTADO");
        return create_bignumber();
    }
}
