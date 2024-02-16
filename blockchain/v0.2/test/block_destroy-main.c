#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "blockchain.h"

void _blockchain_destroy(blockchain_t *blockchain);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	blockchain_t *blockchain;
	block_t *first, *block1;

	blockchain = blockchain_create();
	first = llist_pop(blockchain->chain);
	block1 = block_create(first, (int8_t *)"Holberton", 9);

	block_destroy(first);
	block_destroy(block1);

	_blockchain_destroy(blockchain);

	return (EXIT_SUCCESS);
}