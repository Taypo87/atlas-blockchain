#include "blockchain.h"

blockchain_t *blockchain_create(void)
{
    blockchain_t *blockchain = calloc(sizeof(blockchain_t), 1);
    block_t *genesis_block = calloc(sizeof(block_t), 1);
    block_info_t gen_block_info;
    block_data_t gen_block_data;
    uint8_t genesis_hash[BLOCKCHAIN_DATA_MAX] = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03";
    uint8_t data[] = {'H', 'o', 'l', 'b', 'e', 'r', 't', 'o', 'n', ' ', 'S', 'c', 'h', 'o', 'o', 'l', '\0'};

    gen_block_info.difficulty = 0;
    gen_block_info.index = 0;
    gen_block_info.nonce = 0;
    gen_block_info.timestamp = 1537578000;
    memset(gen_block_info.prev_hash, 0, BLOCKCHAIN_DATA_MAX); 
    
    gen_block_data.len = (uint32_t)(sizeof(data) - 1);
    memcpy(gen_block_data.buffer, data, gen_block_data.len);

    genesis_block->data = gen_block_data;
    genesis_block->info = gen_block_info;
    memcpy(genesis_block->hash, genesis_hash, BLOCKCHAIN_DATA_MAX);

    blockchain->chain = llist_create(MT_SUPPORT_FALSE);
    llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT);
    return (blockchain);

    
}