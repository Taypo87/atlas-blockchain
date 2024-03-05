#include "blockchain.h"
/**
 * block_destroy - destroys a given block in the blockchain
 * @block: the block to destroy
*/
void block_destroy(block_t *block)
{
	llist_destroy(block->transactions, 1,
	 free);
	free(block);
}
