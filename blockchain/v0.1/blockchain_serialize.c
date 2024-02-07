#include "blockchain.h"
#include "provided/endianness.h"

/**
 * block_write - saves a block in the chain to file
 * @node: the block
 * @idx: index
 * @arg: custom args, in this case the FILE *fp;
 * Return: 1 on sucess, else 0
*/
static int block_write(llist_node_t node, unsigned int idx, void *arg)
{
	block_t *block = (block_t *)node;
	FILE *fp = (FILE *)arg;

	fwrite(&idx, 1, 4, fp);
	fwrite(&block->info.difficulty, 1, 4, fp);
	fwrite(&block->info.timestamp, 1, 8, fp);
	fwrite(&block->info.nonce, 1, 8, fp);
	fwrite(block->info.prev_hash, 1, 32, fp);
	fwrite(&block->data.len, 1, 4, fp);
	fwrite((void *)block->data.buffer, 1, block->data.len, fp);
	fwrite((void *)block->hash, 1, 32, fp);
	return (0);
}
/**
 * blockchain_serialize - saves a blockchain to disk
 * @blockchain: the blockchain to be saved
 * @path: the file path to save the blockchain
 * Return: 0 on success, -1 for error
*/
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fp;
	node_func_t action;
	unsigned char num_blocks;
	unsigned char magic_num[4] = {'H', 'B', 'L', 'K'}, hblk_ver[3] = {'0', '.', '1'}, endian;

	endian = _get_endianness();
	action = block_write;
	fp = fopen(path, "wb");
	if (!fp)
		return (-1);
	fwrite(magic_num, 1, 4, fp);
	fwrite(hblk_ver, 1, 3, fp);
	fwrite(&endian, 1, 1, fp);
	num_blocks = llist_size(blockchain->chain);
	fwrite(&num_blocks, 1, 4, fp);
	if (llist_for_each(blockchain->chain, action, fp) < 0)
		return (-1);
	fclose(fp);
	return (0);

}
