CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -Ofast

tp2: tp2.c graph.c queue.c process_input.c
	$(CC) $(CFLAGS) tp2.c graph.c queue.c process_input.c -o tp2 -lm