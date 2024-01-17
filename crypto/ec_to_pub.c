#include "hblk_crypto.h"
/**
 * ec_to_pub - converts and reutrns a public key
 * @key: they private/public key struct
 * pub: buffer to store the public key
 * Return: pub
*/
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	EC_POINT const *public_point;
	EC_GROUP const *group;
	BN_CTX *ctx;

	ctx = BN_CTX_new();
	public_point = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);
	EC_POINT_point2oct(group, public_point, POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, ctx);
	return(pub);
}
