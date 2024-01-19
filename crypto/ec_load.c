#include "hblk_crypto.h"
/**
 * ec_load - loads an ec key pair from disk
 * @folder: the folder containing the ec key pair
 * Return: EC_KEY struct containing the ec key pair
*/
EC_KEY *ec_load(char const *folder)
{
    FILE *fp;
    EC_KEY *key;
    size_t size = (strlen(folder) + 9);
    char *fname = "key.pem";
    char *fullpath = malloc(sizeof(char) * size);

    key = EC_KEY_new();
    snprintf(fullpath, size, "%s/%s", folder, fname);
    fp = fopen(fullpath, "w");
    key = PEM_read_ECPrivateKey(fp, &key, NULL, NULL);
    fclose(fp);
    return (key);
}
