#include "blockchain.h"
#include "provided/endianness.h"

static int check_num(unsigned char *magic_num)
{
    unsigned char static_num[4] = {'H', 'B', 'L', 'K'};
    int i = 0;
    while (i < 4)
    {
        if (magic_num[i] != static_num[i])
            return (0);
        i++;
    }
    return (1);

}

static int check_version(unsigned char *version)
{
    unsigned char static_num[3] = {'0', '.', '1'};
    int i = 0;
    while (i < 3)
    {
        if (version[i] != static_num[i])
            return (0);
        i++;
    }
    return (1);

}

blockchain_t *blockchain_deserialize(char const *path)
{
    FILE *fp;
    block_t *block;
    block_info_t block_info;
    block_data_t block_data;
    blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));
    uint8_t num_blocks = 0, i;
    unsigned char four_[4];
    
    blockchain->chain = llist_create(MT_SUPPORT_FALSE);
    fp = fopen(path, "rb");
    if (!fp)
        return (NULL);
    fread(four_, 1, 4, fp);
    if (!check_num(four_))
        return (NULL);
    fread(four_, 1, 3, fp);
    if (!check_version(four_))
        return (NULL);
    fread(four_, 1, 1, fp);
    if (_get_endianness() != four_[0])
        puts("endianness does not match\n");
    fread(&num_blocks, 1, 4, fp);
    for (i = 0; i < num_blocks; i++)
    {
        block = calloc(1 , sizeof(block_t));
        fread(&block_info.index, 1, 4, fp);
        fread(&block_info.difficulty, 1, 4, fp);
        fread(&block_info.timestamp, 1, 8, fp);
        fread(&block_info.nonce, 1, 8, fp);
        fread(&block_info.prev_hash, 1 ,32, fp);
        fread(&block_data.len, 1, 4, fp);
        fread(block_data.buffer, 1, block_data.len, fp);
        fread(block->hash, 1, 32, fp);
        block->data = block_data;
        block->info = block_info;
        llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
    }

    return (blockchain);

    
}