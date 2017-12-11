#include "DES.h"
#include <stdio.h>
#include <string>

uint16_t decrypt( uint16_t c , uint16_t k)
{
   short L,R;

   DES::LR( c, L, R);
   uint16_t m = DES::unLR(R,L);

   for( int i = 0; i < 4; i++)
   {
      m = DES::round( m, k, ( 3 - i ) );
   }
   DES::LR( m, L, R);
   return  DES::unLR(R,L);

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

   uint16_t pb[4];

   buff.u48 = 0;

   size_t result = fread( &buff , 6 , 1 , stdin);
   buff.u48=  htole64(buff.u48);

   while(result == 1)
   {

      DES::charto12( buff.b, pb);

      for( int i = 0; i < 4; i ++)
      {
         pb[i] = decrypt( pb[i], key );
      }

      buff.u48= 0;

      DES::charfrom12( pb , buff.b);

      fwrite( buff.b, 6, 1, stdout);

      buff.u48 = 0;
      result = fread( &buff , 6 , 1 , stdin);
   }
}
