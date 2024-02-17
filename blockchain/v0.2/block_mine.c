#include "blockchain.h"
/**
 * block_mine - mines a block
 * @block: the block to be mined
*/
void block_mine(block_t *block)
{
	uint32_t buff[SHA256_DIGEST_LENGTH];

	block_hash(block, buff);

	while (!hash_matches_difficulty(buff, block->info.difficulty))
	{
		block->info.nonce++;
		block_hash(block, buff);
	}
}
