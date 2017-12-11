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
