/*
usage: ./decrypt <key> < plaintext >cyphertext
 */
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string ADFGX[]{
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
   string c;
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
bool check_overflow( char c, int overflow, string key )
{
   size_t pos = key.find( c );
   if( pos > overflow )
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

   for( auto i : key )
   {
      column temp;
      temp.label = i;
      cols.push_back(temp);
   }

   string text;
   char c = fgetc( stdin );

   while( c != EOF )
   {
      c = toupper(c);
      if( c >= 'A' && c <= 'Z' )
      {
         text.push_back(c);
      }
      c = fgetc( stdin );
   }


   sort( cols.begin(), cols.end(), col_compare);

   int per = ( text.length() / key.length());
   int overflow = ( text.length() % key.length()) /2;
   auto it = text.begin();

   for( auto& j : cols )
   {
      for( int i = 0; i < per; i++ )
      {
         j.c.push_back(*it);
         it++;
      }
      if( check_overflow( j.label, overflow, key ) )
      {
         j.c.push_back(*it);
         it++;
      }
   }

   vector<column> reorder;

   for( auto i: key)
      for( auto& j : cols )
         if( i == j.label )
         {
            reorder.push_back(j );
         }

   string reorderedtext;
   
   for( int i = 0 ; i < text.length(); i++ )
   {
      reorderedtext.push_back(reorder[i%key.length()].c[i/key.length()]);
   }

   for( int i = 0 ; i < reorderedtext.length()-1; i+=2 )
   {
      string findstr = reorderedtext.substr( i, 2);
      int cha = ( find( ADFGX, ADFGX+25, findstr ) - ADFGX+25)-25;
      cout << char('a' + cha);
   }
}
