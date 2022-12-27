 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <libakrypt.h>

size_t blok_size = 64;
static ak_uint8 crc_M1_message[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};

static ak_uint8 crc64_testM1[] = {0x36, 0x32, 0xC4, 0x18, 0x0E, 0x36, 0xE1, 0x91};

// 36 32 c4 18 0e 36 e1 91

/* ----------------------------------------------------------------------------------------------- */
int main( void )
{ 
  struct hash struct_hash;
  ak_uint8 out[4];
  struct_hash.data.crcctx.hsize = 5;
  struct_hash.data.crcctx.mode = 64;

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
  printf(ak_ptr_to_hexstr(struct_hash.data.crcctx.sigma, 8, ak_true));
  printf("\n");
  printf("right value: ");
  printf(ak_ptr_to_hexstr(crc64_testM1, 8, ak_true));
  printf("\n\n");

  if(ak_ptr_is_equal_with_log( struct_hash.data.crcctx.sigma, crc64_testM1, 8 ) != ak_true ) {
    printf("the 1st test crc64 is wrong\n" );
    ak_hash_destroy(&struct_hash);
    return EXIT_FAILURE;
  }


 return EXIT_SUCCESS;
}
