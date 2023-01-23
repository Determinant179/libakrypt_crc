 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <libakrypt.h>

size_t blok_size = 64;
static ak_uint8 crc_M1_message[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};

ak_uint64 crc64_testM1 = 3905399434480378257;

/* ----------------------------------------------------------------------------------------------- */
int main( void )
{ 
  struct hash struct_hash;
  ak_uint8 out[4];
  struct_hash.data.crcctx.hsize = 5;
  struct_hash.data.crcctx.seed = 0xC96C5795D7870F42;
  struct_hash.data.crcctx.mask = 0xFFFFFFFFFFFFFFFF;

  int error = ak_error_ok;

  if(( error = ak_hash_create_crc32 ( &struct_hash )) != ak_error_ok ) {
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }

  ak_hash_ptr( &struct_hash, crc_M1_message, 64, out, sizeof( out ));
  if(( error = ak_error_get_value()) != ak_error_ok ) {
    printf("invalid calculation of crc64 code\n" );
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }

  printf("\ninput: ");
  printf(ak_ptr_to_hexstr(crc_M1_message, 5, ak_true));
  printf("\n");
  printf("hash: ");
  printf("%llx", struct_hash.data.crcctx.sigma);
  printf("\n");
  printf("right value: ");
  printf("%llx", crc64_testM1);
  printf("\n\n");

  if(struct_hash.data.crcctx.sigma != crc64_testM1) {
    printf("the 1st test crc64 is wrong\n" );
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }


 return EXIT_SUCCESS;
}
