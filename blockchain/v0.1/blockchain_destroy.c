#include "blockchain.h"

void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy((llist_t *)blockchain->chain, 
		llist_size((llist_t *)blockchain->chain), NULL);
	free(blockchain);
}
