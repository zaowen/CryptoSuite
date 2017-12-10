/*
usage: ./encrypt <key> < plaintext >cyphertext
*/
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

char ADFGX[][26]{
"FF", //a
"DA", //b
"AF", //c
"GD", //d
"AG", //e
"FG", //f
"AD", //g
"XX", //h
"GG", //i
"GG", //j
"XA", //k
"FD", //l
"GA", //m
"AX", //n
"DF", //o
"AA", //p
"DD", //q
"DX", //r
"FA", //s
"FX", //t
"XD", //u
"GD", //v
"GX", //w
"XG", //x
"XF", //y
"DG"  //z
};

struct column {
   std::vector<char> c;
   char label;

};

bool parse_key( string &key )
{
   auto it = unique( key.begin(), key.end() );
   key.resize( std::distance(key.begin(),it) );

   if( key.length() <= 2 )
   {
      return false;
   }
   return true;
}

bool col_compare(column n, column m){ return (n.label < m.label); }

int main( int argc, char*argv[])
{
   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <key>\n", argv[0] );
      return -1;
   }

   string key = argv[1];
   vector<column> cols;
   if( !parse_key( key ) )
   {
      fprintf( stderr, "Invalid Key", argv[0] );
   }

   size_t keylen =  key.length();

   for( auto i : key )
   {
      column temp;
      temp.label = i;
      cols.push_back(temp);
   }


   int i = 0;
   string text;

   char c = fgetc( stdin );

   while( c != EOF )
   {
      c = tolower(c);
      if( c >= 'a' && c <= 'z' )
      {
         text.append( ADFGX[c-'a'] );
      }
      c = fgetc( stdin );
   }
   //DEBUG cout << text << endl;

   auto ch = text.begin();
   
   int j = 0;
   for( auto i : text )
   {
      cols[j%keylen].c.push_back( i );
      j++;
   }

   /* DEBUG
   for( auto i : cols )
   {
      cout << i.label << ":";
      for( auto k : i.c )
         cout << k;
      cout << endl;
   }
   */

   sort( cols.begin(), cols.end(), col_compare);

   for( auto i : cols )
   {
      for( auto k : i.c )
         cout << k;
   }
}
