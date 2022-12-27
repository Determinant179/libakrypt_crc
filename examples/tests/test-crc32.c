 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <libakrypt.h>

size_t blok_size = 32;
static ak_uint8 crc_M1_message[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};


 static ak_uint8 crc32_testM1[] = {0xF7, 0xD1, 0x89, 0x82};

// f7d18982

/* ----------------------------------------------------------------------------------------------- */
int main( void )
{ 
  struct hash struct_hash;
  ak_uint8 out[4];
  struct_hash.data.crcctx.hsize = 5;
  struct_hash.data.crcctx.mode = 32;

  int error = ak_error_ok;

  if(( error = ak_hash_create_crc32 ( &struct_hash )) != ak_error_ok ) {
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }

  ak_hash_ptr( &struct_hash, crc_M1_message, 32, out, sizeof( out ));
  if(( error = ak_error_get_value()) != ak_error_ok ) {
    printf("invalid calculation of crc32 code\n" );
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }

  printf("\ninput: ");
  printf(ak_ptr_to_hexstr(crc_M1_message, 5, ak_true));
  printf("\n");
  printf("hash: ");
  printf(ak_ptr_to_hexstr(struct_hash.data.crcctx.sigma, 4, ak_true));
  printf("\n");
  printf("right value: ");
  printf(ak_ptr_to_hexstr(crc32_testM1, 4, ak_true));
  printf("\n\n");

  if(ak_ptr_is_equal_with_log( struct_hash.data.crcctx.sigma, crc32_testM1, 4 ) != ak_true ) {
    printf("the 1st test crc32 is wrong\n" );
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }


 return EXIT_SUCCESS;
}
