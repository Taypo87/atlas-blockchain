#include "transaction.h"

/**
 * tx_out_create - creates and initializes a tx_out_t struct
 * @amount: the amount of the transaction
 * @pub: the public key of transaction receiver
 * Return: pointer to the newly created struct
*/

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
    tx_out_t *new = calloc(1, sizeof(tx_out_t));
    SHA256_CTX ctx;

    if (new == NULL)
        return (NULL);
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, &amount, strlen(amount));
    SHA256_Update(&ctx, pub, EC_PUB_LEN);
    SHA256_Final(new->hash, &ctx);
    new->amount = amount;
    memcpy(new->pub, pub, EC_PUB_LEN);
    
    return (new);

}
