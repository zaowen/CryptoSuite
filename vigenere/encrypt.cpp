/*
usage: ./encrypt <key> < plaintext >cyphertext
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char*argv[])
{
   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <key>\n", argv[0] );
      return -1;
   }

   char * key = argv[1];
   size_t keylen = strlen( key );

   int i = 0;

   char c = fgetc( stdin );

   while( c != EOF )
   {
      c = tolower(c);
      if( c >= 'a' && c <= 'z' )
      {
         c = c - 'a';
         c = (c + key[i]) % 26;
         c = c + 'a';
      }

      fputc(c, stdout );
      i = (i + 1) % keylen;

      c = fgetc( stdin );
   }
} 
