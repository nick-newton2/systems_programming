/* hash.c: hash functions */

#include "hash.h"

#include <stdio.h>

/**
 * Constants
 * http://isthe.com/chongo/tech/comp/fnv/
 */

#define FNV_OFFSET_BASIS    (0xcbf29ce484222325ULL)
#define FNV_PRIME           (0x100000001b3ULL)

/**
 * Compute FNV-1 hash.
 * @param   data            Data to hash.
 * @param   n               Number of bytes in data.
 * @return  Computed hash as 64-bit unsigned integer.
 */
uint64_t    hash_from_data(const void *data, size_t n) {
    uint64_t hash = FNV_OFFSET_BASIS;
    uint8_t *byte = (uint8_t *)data;

    for(size_t i =0; i <n; i++){
      hash= hash ^ byte[i];
      hash= hash *FNV_PRIME;
    }

    return hash;
}

/**
 * Compute MD5 digest.
 * @param   path            Path to file to checksum.
 * @param   hexdigest       Where to store the computed checksum in hexadecimal.
 * @return  Whether or not the computation was successful.
 */
bool        hash_from_file(const char *path, char hexdigest[HEX_DIGEST_LENGTH]) {
  MD5_CTX ctx;
  uint8_t buff[BUFSIZ];
  uint8_t rawdig[MD5_DIGEST_LENGTH];
  ssize_t bytes;

  MD5_Init(&ctx);

  FILE *f= fopen(path, "r");
  if(!f) return -1;

  bytes= fread(buff, 1, BUFSIZ, f);
  while(bytes > 0){
    MD5_Update(&ctx, buff, bytes);
    bytes= fread(buff, 1, BUFSIZ, f);
  }

  fclose(f);

  MD5_Final(rawdig, &ctx);
  int i;
  for(i=0; i<MD5_DIGEST_LENGTH; i++){
    sprintf(hexdigest +2 * i, "%02x", rawdig[i]);
  }

  return true;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
