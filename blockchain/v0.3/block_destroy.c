#include "blockchain.h"
/**
 * block_destroy - destroys a given block in the blockchain
 * @block: the block to destroy
*/
void block_destroy(block_t *block)
{
	int list_size;

	list_size = llist_size(block->transactions);
	llist_destroy(block->transactions, list_size, transaction_destroy);
	free(block);
}
