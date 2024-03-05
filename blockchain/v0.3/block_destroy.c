#include "blockchain.h"
/**
 * block_destroy - destroys a given block in the blockchain
 * @block: the block to destroy
*/
void block_destroy(block_t *block)
{
	llist_destroy(block->transactions, 1,
	 (node_dtor_t)transaction_destroy);
	free(block->hash);
	free(block->transactions);
	free(block);
}
