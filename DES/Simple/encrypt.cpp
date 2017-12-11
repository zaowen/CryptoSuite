#include "DES.h"
#include <stdio.h>
#include <endian.h>


int main( int argc, char* argv[] )
{

   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <HEX-key>\n", argv[0] );
      return -1;
   }

   uint16_t key = DES::getKey( argv[1] );

   union {
      uint64_t u48;
      uint8_t b[8];
   } buff;

   uint16_t cb[4];

   buff.u48 = 0;
   size_t result = fread( &buff , 6 , 1 , stdin);
   buff.u48=  htole64(buff.u48);

   while(result == 1)
   {

      DES::charto12( buff.b, cb);

      for( int i = 0; i < 4; i ++)
      {
         cb[i] = DES::encrypt( cb[i], key );
      }

      buff.u48= 0;

      DES::charfrom12( cb , buff.b);

      fwrite( buff.b, 6, 1, stdout);

      buff.u48 = 0;
      result = fread( &buff , 6 , 1 , stdin);
   }

      DES::charto12( buff.b, cb);

      for( int i = 0; i < 4; i ++)
      {
         cb[i] = DES::encrypt( cb[i], key );
      }

      buff.u48= 0;

      DES::charfrom12( cb , buff.b);

      fwrite( buff.b, 6, 1, stdout);

}
