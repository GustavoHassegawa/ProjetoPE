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

BigNumber create_bignumber_zero();

void add_digit_end(BigNumber number, int digit);

void add_digit_head(BigNumber number, int digit);

void erase_digit_head(BigNumber number);

void erase_digit_end(BigNumber number);

int return_digit(char character);

BigNumber char_bignumber(char *string);

void read_bignumber(BigNumber number);

void print_bignumber(BigNumber number);

void erase_bignumber(BigNumber number);

void delete_left_zeros(BigNumber number);

int is_equal(BigNumber a, BigNumber b);

int is_bigger(BigNumber a, BigNumber b);

void node_modularizer(BigNumber number);

BigNumber sum_bignumber(BigNumber number1, BigNumber number2);

void sum_bignumber_void(BigNumber number, BigNumber out);

BigNumber sub_bignumber(BigNumber minuend, BigNumber subtrahend);

void sub_bignumber_void(BigNumber number, BigNumber out);

BigNumber multi_bignumber(BigNumber Multiplicand, BigNumber Multiplier);

BigNumber div_bignumber(BigNumber dividend, BigNumber divisor);

BigNumber identify(BigNumber numberA, BigNumber numberB, char operation);

#endif
