#ifndef _TRANSACTIONS_
#define _TRANSACTIONS_

#include "../blockchain.h"



tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);
unspent_tx_out_t *unspent_tx_out_create(uint8_t block_hash[SHA256_DIGEST_LENGTH],
                        uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out);

#endif 

