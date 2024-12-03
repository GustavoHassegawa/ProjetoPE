#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct node {
    short int digit;
    struct node *prev;
    struct node *next;
} *Node;

typedef struct bignumber {
    Node begin;
    Node end;
} *BigNumber;

BigNumber create_bignumber();

void add_digit(BigNumber number, int digit);

int return_digit(char character);

BigNumber char_bignumber(char *string);

void print_bignumber(BigNumber number);

void erase_bignumber(BigNumber number);

#endif
