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
    blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));
    uint8_t *num_blocks;
    unsigned char four_[4];

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
    fread(num_blocks, 1, 4, fp);
    printf("%d\n", *num_blocks);
    return (blockchain);

    
}