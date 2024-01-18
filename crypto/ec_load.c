#include "hblk_crypto.h"
//reading the private key should also load the public key


static int read_private()
{

}


EC_KEY *ec_load(char const *folder)
{

}


EC_KEY *PEM_read_EC_PUBKEY(FILE *fp, EC_KEY **x, pem_password_cb *cb, void *u);
EC_KEY *PEM_read_ECPrivateKey(FILE *out, EC_KEY **x, pem_password_cb *cb, void *u);