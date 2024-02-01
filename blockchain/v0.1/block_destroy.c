#include "blockchain.h"
/**
 * block_destroy - destroys a given block in the blockchain
 * @block: the block to destroy
*/
void block_destroy(block_t *block)
{
	free(block->data.buffer);
	free(block->hash);
	free(block->info.prev_hash);
	free(block);
}
