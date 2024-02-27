#ifndef _TRANSACTIONS_
#define _TRANSACTIONS_

#include "../blockchain.h"



tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);

#endif 

