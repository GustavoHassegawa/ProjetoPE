#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include <stdio.h>
#include <stdbool.h>

typedef struct node {
    short int digit;
    struct node *prev;
    struct node *next;
} *Node;

typedef struct bignumber {
    Node begin;
    Node end;
    int size;
    bool negative;
} *BigNumber;

BigNumber create_bignumber();

void add_digit_end(BigNumber number, int digit);

int return_digit(char character);

BigNumber char_bignumber(char *string);

void read_bignumber(BigNumber number);

void print_bignumber(BigNumber number);

void erase_bignumber(BigNumber number);

BigNumber sum_bignumber(BigNumber number1, BigNumber number2);

void delete_left_zeros(BigNumber number);

void node_modularizer(BigNumber number);

BigNumber sub_bignumber(BigNumber minuend, BigNumber subtrahend);

#endif
