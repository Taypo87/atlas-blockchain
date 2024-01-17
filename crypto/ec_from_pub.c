#include "hblk_crypto.h"
/**
 * ec_from_pub - sets an EC_KEY object with a public key
 * @pub: the public key
 * Return: the EC_KEY
*/
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_POINT *p;
	EC_GROUP const *group;
	BN_CTX *ctx;

	key = EC_KEY_new();
	ctx = BN_CTX_new();
	group = EC_GROUP_new_by_curve_name(EC_CURVE);
	EC_KEY_set_group(key, group);
	p = EC_POINT_new(group);
	EC_POINT_oct2point(group, p, pub, (EC_PUB_LEN), ctx);
	EC_KEY_set_public_key(key, p);

	return (key);
}
