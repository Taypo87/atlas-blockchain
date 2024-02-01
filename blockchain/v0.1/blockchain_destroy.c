#include "blockchain.h"

void blockchain_destroy(blockchain_t *blockchain)
{
	while (llist_size((llist_t *)blockchain) > 0)
	{
		block_destroy((block_t *)llist_pop((llist_t *)blockchain));
	}
	llist_destroy((llist_t *)blockchain, 0, NULL);
}
