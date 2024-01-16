#include "hblk_crypto.h"

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
    BN_CTX *ctx;

    ctx = BN_CTX_new();
 
    EC_KEY_oct2key((EC_KEY *)key, pub, EC_PUB_LEN, ctx);
    return(pub);
    
}
