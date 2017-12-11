#include "DES.h"
#include <stdio.h>
#include <string>
#include <endian.h>

uint16_t encrypt( uint16_t m , uint16_t k)
{
   uint16_t c = m;

   for( int i = 0; i < 4; i++)
   {
      c = DES::round( c, k, i );
   }

   return c;
}

uint16_t getKey( char * str )
{
   try{
      return std::stoi( str, NULL, 16);
   } catch( const std::exception& e){
      fprintf( stderr, "PROBLEM INTERPRETING KEY" );
      exit( -1 );
   } 
}

int main( int argc, char* argv[] )
{

   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <HEX-key>\n", argv[0] );
      return -1;
   }

   uint16_t key = getKey( argv[1] );

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
         cb[i] = encrypt( cb[i], key );
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
         cb[i] = encrypt( cb[i], key );
      }

      buff.u48= 0;

      DES::charfrom12( cb , buff.b);

      fwrite( buff.b, 6, 1, stdout);

}
