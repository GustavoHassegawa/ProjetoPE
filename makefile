all: client

client: client.o bignumber.o
	gcc client.o bignumber.o -g -lm -o client

client.o: client.c bignumber.h
	gcc -std=c99 -Wall -Wvla -g -c client.c

bignumber.o: bignumber.c bignumber.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c bignumber.c
