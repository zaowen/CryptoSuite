/*
usage: ./encrypt <key> < plaintext >cyphertext
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char*argv[])
{
   int arr[26] = {0};
   char c = fgetc( stdin );
   while( c != EOF )
   {
      c = tolower(c);
      if( c >= 'a' && c <= 'z' )
      {
         arr[c-'a']++;
      }
      c = fgetc( stdin );
   }

   printf("Freq Arr:");
   printf("[a]=%d, ",arr[0] );
   for( int i = 1 ; i < 26; i++ )
   {
      printf("[%c]=%d, ", 'a' +i,arr[i] );
   }
} 
