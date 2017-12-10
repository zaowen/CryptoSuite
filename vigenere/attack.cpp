
/*
usage: ./attack <file>
note: guesses poorly for short key lengths
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFSIZE 256
#define MAXKEY 64

int collisions( int disp, char buff[] )
{
   int col = 0;
   for( int i=0; i < BUFFSIZE - disp; i++)
   {
      if( buff[i] == buff[i+disp] )
      {
         col++;
      }
   }

   return col;
}

int find_keylen( FILE * fp )
{
   char buffer[BUFFSIZE];
   short match[MAXKEY] = {0};
   int max = 0;

   fgets(buffer, BUFFSIZE, fp);
   do{
      for( int i = 1 ; i < MAXKEY; i++ )
      {
         match[i] += collisions(i,buffer);
      }
   } while( fgets(buffer, BUFFSIZE, fp) != NULL );

   for( int i = 1 ; i < MAXKEY; i++ )
   {
      //printf( "# of collisions for key length %d:\t%d\n",i,match[i]);
      if( match[i] > match[max] )
      {
         max = i;
      }
   }
   return max;

}

char freq_attack( int n , int keylen , FILE *fp )
{
   int arr[26] = {0};
   char buffer[keylen+1];

   fgets(buffer, keylen+1, fp);
   do{
      {
         char c = buffer[n];
         arr[ c -'a']++;
      }
   } while( fgets(buffer, keylen+1, fp) != NULL );


   int max = 0;
   for( int i = 1 ; i < 26; i++ )
   {
      if( arr[i] > arr[max] )
      {
         max = i;
      }
   }

   max = max - 4;
   if( max < 0)
   {
      max = max + 26;
   }
   return ( 'a' + max);
}

int main( int argc, char*argv[])
{
   FILE* fp;
   char key[65];
   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <file>\n", argv[0] );
      return -1;
   }

   fp = fopen( argv[1], "r" );

   if( fp == NULL )
   {
      fprintf( stderr, "Could not open file %s\n\tExiting", argv[1]);
      return -1;
   }

   int keylen = find_keylen( fp );

   printf( "Keylength guess:%d\n" , keylen);

   for( int i = 0; i < keylen; i++)
   {
      rewind( fp );
      key[i] = freq_attack( i , keylen , fp );
      key[i+1] = '\0';
   }

   printf( "Key guess:%s\n" , key);

   fclose( fp );
   return 0;
}
