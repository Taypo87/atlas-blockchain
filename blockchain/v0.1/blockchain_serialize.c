#include "blockchain.h"
#include "provided/endianness.h"
/**
 * initialize_header - initilizes the header_t variable
 * @blockchain: the blockchain to generate the header for
 * header_struct_ptr: address of the header struct pointer
 * Return: 0 on mem allocation failure, else 1;
*/
static int initialize_header(blockchain_t *blockchain, header_t **header_struct_ptr)
{
	header_t *header_struct;

	header_struct = malloc(sizeof(header_t));
	if(!header_struct);
		return (0);
	header_struct->hblk_magic = "HBLK";
	header_struct->hblk_version = "1.0";
	header_struct->hblk_endian = _get_endianness();
	header_struct->hblk_blocks = llist_size(blockchain->chain);
	*header_struct_ptr = header_struct;
	return (1);
}
/**
 * initialize_blkmmbr - initializse the block_member_t variable
 * @block: a given block in the blockchain
 * @mmbrs_add: address of the mmbrs struct pointer
*/
static int initialize_blkmmbr(block_t *block, block_members_t **mmbrs_add)
{
	block_members_t *mmbrs;

	mmbrs = malloc(sizeof(block_members_t));
	if (!mmbrs)
		return (0);
	mmbrs->index = block->info.index;
	mmbrs->diff = block->info.difficulty;
	mmbrs->tstamp = block->info.timestamp;
	mmbrs->non_c = block->info.nonce;
	mmbrs->prv_hash = block->info.prev_hash;
	mmbrs->dat_len = block->data.len;
	*mmbrs_add = mmbrs;
	return (1);
}
/**
 * block_write - saves a block in the chain to file
 * @node: the block
 * @idx: index
 * @arg: custom args, in this case the FILE *fp;
 * Return: 1 on sucess, else 0
*/
static int block_write(llist_node_t node, unsigned int idx, void *arg)
{
	llist_node_t *node_ptr;
	block_t *block = (block_t *)node;
	FILE *fp = (FILE *)arg;
	block_members_t *blk_mmbrs;

	if (!initialize_blkmmbr(block, &blk_mmbrs))
		return(-1);
	fwrite(blk_mmbrs, sizeof(block_members_t), 1, fp);
	fwrite((void *)block->data.buffer, 1, block->data.len, fp);
	fwrite((void *)block->hash, 1, 32, fp);
	free(blk_mmbrs);
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
	header_t *header_struct;
	node_func_t *action;
	void *write_pointer;

	
	action = block_write;
	fp = fopen(path, "wb");
	if (!initialize_header(blockchain, &header_struct) || !fp)
		return (-1);
	fwrite((void *)header_struct, sizeof(header_t), 1, fp);
	free(header_struct);
	if (llist_for_each(blockchain->chain, action, fp) < 0)
		return (-1);
	fclose(fp);
	return (0);

}
