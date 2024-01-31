#include "blockchain.h"

blockchain_t *blockchain_create(void)
{
    blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));
    block_t *genesis_block = calloc(1, sizeof(block_t));
    uint8_t genesis_hash[BLOCKCHAIN_DATA_MAX] = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03";
    uint8_t data[] = {'H', 'o', 'l', 'b', 'e', 'r', 't', 'o', 'n', ' ', 'S', 'c', 'h', 'o', 'o', 'l', '\0'};

    genesis_block->info.timestamp = 1537578000;

    memset(genesis_block->info.prev_hash, 0, BLOCKCHAIN_DATA_MAX); 
    
    genesis_block->data.len = strlen((char)(data));
    memcpy(genesis_block->data.buffer, data, genesis_block->data.len);

    memcpy(genesis_block->hash, genesis_hash, BLOCKCHAIN_DATA_MAX);

    blockchain->chain = llist_create(MT_SUPPORT_TRUE);
    llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT);
    return (blockchain);

    
}