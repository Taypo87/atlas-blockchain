#include "blockchain.h"

void blockchain_destroy(blockchain_t *blockchain)
{
	blk_destroy_ptr = block_destroy;
	llist_destroy((llist_t *)blockchain, llist_size((llist_t *)blockchain), NULL);
}
