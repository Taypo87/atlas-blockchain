#include "blockchain.h"

/**
 * blockchain_destroy - frees a blockchain
 * @blockchain: pointer to the blockchain to free
*/
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy((llist_t *)blockchain->chain,
		1, free);
	llist_destroy(blockchain->chain, 1, free);
	free(blockchain);
}
