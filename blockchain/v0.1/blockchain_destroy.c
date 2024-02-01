#include "blockchain.h"
/**
 * blockchain_destroy - frees all the blocks and the blochain itself
*/
void blockchain_destroy(blockchain_t *blockchain)
{
	void (*blk_dstry_ptr)(block_t *);
	blk_dstry_ptr = block_destroy();
	llist_destroy(blockchain, llist_size(blockchain), blk_dstry_ptr);
}
