#include "blockchain.h"

/**
 * blockchain_destroy - frees a blockchain
 * @blockchain: pointer to the blockchain to free
*/
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy((llist_t *)blockchain->chain,
		1, (node_dtor_t)block_destroy);
	free(blockchain);
}
