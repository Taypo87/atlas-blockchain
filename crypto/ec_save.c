#include "hblk_crypto.h"

int write_private(EC_KEY *key, char const *folder)
{
    FILE *fp;
    int written;
    size_t path_len = strlen(folder) + strlen("/key.pem") + 3;
    char *priv_path = malloc(sizeof(char) * (path_len));
    char *file_name = "key.pem";

    snprintf(priv_path, path_len, "%s/%s", folder, file_name);
    printf("path is %s\n", priv_path);
    fp = fopen(priv_path, "w");
    if (!fp)
        printf("failed to open file\n");
    written = PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
    printf("wrttien = %d\n", written);
    fclose(fp);
    free(priv_path);
    return (written > 0 ? 1 : 0);
}

int write_public(EC_KEY *key, char const *folder)
{
    FILE *fp;
    size_t path_len = strlen(folder) + strlen("/key_pub.pem") + 3;
    char *pub_path = malloc(sizeof(char) * (path_len));
    char *file_name = "pub_key.pem";
    int written = 0;

    snprintf(pub_path, path_len, "%s/%s", folder, file_name);
    printf("public path is %s\n", pub_path);
    fp = fopen(pub_path, "w");
    if (!fp)
        printf("failed to open file\n");
    written = PEM_write_EC_PUBKEY(fp, key);
    printf("wrttien = %d\n", written);
    fclose(fp);
    free(pub_path);
    return (written > 0 ? 1 : 0);
}

static int handle_path(char *folder)
{
    struct stat st = {0};

    if (stat((char *)folder, &st) == -1)
    {
        if (mkdir((char *)folder, 0777) == -1)
        {
            perror("mkdir");
            return (0);
        }
    }
    return (1);
}

int ec_save(EC_KEY *key, char const *folder)
{
    char *path, **selector, *folder_temp = (char *)folder;

    if (!key)
        return (0);
    selector = &folder_temp;
    path = malloc(sizeof(char *) * (strlen(folder) + 2));
    if (folder[0] != '/' && folder[0] != '.')
    {
        snprintf(path, (strlen(folder) + 2), "/%s", folder);
        selector = &path;
    }
    handle_path(*selector);
    if (!write_private(key, *selector) || !write_public(key, *selector))
        return(0);
    return (1);

}

