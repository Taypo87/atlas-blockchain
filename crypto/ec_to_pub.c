#include "hblk_crypto.h"

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
    //EC_POINT const *point;
    //const EC_GROUP *group;
    //point_conversion_form_t form;
    BN_CTX *ctx;

    ctx = BN_CTX_new();
    //point = EC_KEY_get0_public_key(key);
   // group = EC_KEY_get0_group(key);
    //form = EC_KEY_get_conv_form(key);
    EC_KEY_oct2key((EC_KEY *)key, pub, EC_PUB_LEN, ctx);
    return(pub);
    
}
