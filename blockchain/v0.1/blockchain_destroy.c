#include "blockchain.h"

void blockchain_destroy(blockchain_t *blockchain)
{
	while (llist_size((llist_t *)blockchain) > 0)
	{
		block_destroy(llist_pop((llist_t *)blockchain));
	}
	llist_destroy(blockchain, 0, NULL);
}
