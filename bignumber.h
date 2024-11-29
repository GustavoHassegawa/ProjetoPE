#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct node {
    int digit;
    Node prev;
    Node next;
} *Node;

typedef struct bignumber {
    Node begin;
    Node end;
} *BigNumber;

BigNumber create_bignumber();

void add_digit(BigNumber number, int digit);

#endif
