#include "DES.h"
#include <stdio.h>

int main( int argc, char* argv[] )
{
   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <HEX-key>\n", argv[0] );
      return -1;
   }

   uint64_t key = DES::getKey( argv[1] );

   uint64_t m,k,c;
   uint64_t buff = 0;
   uint64_t cb;

   m = 0x0123456789ABCDEF;
   k = 0x133457799BBCDFF1;

   fprintf( stderr, "MEssage:%llX\tKey:%llX\n",m,k);

   c = DES::encrypt( m, k );

   fprintf( stderr, "Cyphertext:%llX\n", c);
   fwrite( &c, 16, 1, stdout);

   return 0;


   size_t result = fread( &buff , 16 , 1 , stdin);

   while(result == 1)
   {

      cb = DES::encrypt( buff, key );

      fwrite( &cb, 16, 1, stdout);

      buff = 0;
      result = fread( &buff , 16 , 1 , stdin);
   }

      cb = DES::encrypt( buff, key );

      fwrite( &cb, 16, 1, stdout);

}
