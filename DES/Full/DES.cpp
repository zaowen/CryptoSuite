#include "DES.h"
#include <stdio.h>
#include <string>

namespace DES
{
   short IP[64]={
      58 ,50 ,42 ,34 ,26 ,18 ,10 ,2,
      60 ,52 ,44 ,36 ,28 ,20 ,12 ,4,
      62 ,54 ,46 ,38 ,30 ,22 ,14 ,6,
      64 ,56 ,48 ,40 ,32 ,24 ,16 ,8,
      57 ,49 ,41 ,33 ,25 ,17 ,9 ,1,
      59 ,51 ,43 ,35 ,27 ,19 ,11 ,3,
      61 ,53 ,45 ,37 ,29 ,21 ,13 ,5,
      63 ,55 ,47 ,39 ,31 ,23 ,15 ,7};

   short IPinv[64]={
      40 ,8 ,48 ,16 ,56 ,24 ,64 ,32,
      39 ,7 ,47 ,15 ,55 ,23 ,63 ,31,
      38 ,6 ,46 ,14 ,54 ,22 ,62 ,30,
      37 ,5 ,45 ,13 ,53 ,21 ,61 ,29,
      36 ,4 ,44 ,12 ,52 ,20 ,60 ,28,
      35 ,3 ,43 ,11 ,51 ,19 ,59 ,27,
      34 ,2 ,42 ,10 ,50 ,18 ,58 ,26,
      33 ,1 ,41 ,9 ,49 ,17 ,57 ,25};

   short E[48]={
      32 ,1  ,2  ,3  ,4  ,5  ,4  ,5  ,6  ,7  ,8  ,9 ,
      8  ,9  ,10 ,11 ,12 ,13 ,12 ,13 ,14 ,15 ,16 ,17,
      16 ,17 ,18 ,19 ,20 ,21 ,20 ,21 ,22 ,23 ,24 ,25,
      24 ,25 ,26 ,27 ,28 ,29 ,28 ,29 ,30 ,31 ,32 ,1 };

   short PC[]={
      16 ,7 ,20 ,21 ,29 ,12 ,28 ,17,
      1 ,15 ,23 ,26 ,5 ,18 ,31 ,10,
      2 ,8 ,24 ,14 ,32 ,27 ,3 ,9,
      19 ,13 ,30 ,6 ,22 ,11 ,4 ,25};

   short PC1Left[]={
      57 ,49 ,41 ,33 ,25 ,17 ,9,
      1 ,58 ,50 ,42 ,34 ,26 ,18,
      10 ,2 ,59 ,51 ,43 ,35 ,27,
      19 ,11 ,3 ,60 ,52 ,44 ,36};

   short PC1Right[]={
      63 ,55 ,47 ,39 ,31 ,23 ,15,
      7 ,62 ,54 ,46 ,38 ,30 ,22,
      14 ,6 ,61 ,53 ,45 ,37 ,29,
      21 ,13 ,5 ,28 ,20 ,12 ,4};

   short PC2[]={
      14 , 17 , 11 , 24 , 1 , 5,
      3 , 28 , 15 , 6 , 21 , 10,
      23 , 19 , 12 , 4 , 26 , 8,
      16 , 7 , 27 , 20 , 13 , 2,
      41 , 52 , 31 , 37 , 47 , 55,
      30 , 40 , 51 , 45 , 33 , 48,
      44 , 49 , 39 , 56 , 34 , 53,
      46 , 42 , 50 , 36 , 29 , 32
   };

   short rotation[16]={1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,1};

   short sbox0[][16]= {
      {14 ,4 ,13 ,1 ,2 ,15 ,11 ,8 ,3 ,10 ,6 ,12 ,5 ,9 ,0 ,7},
      {0 ,15 ,7 ,4 ,14 ,2 ,13 ,1 ,10 ,6 ,12 ,11 ,9 ,5 ,3 ,8},
      {4 ,1 ,14 ,8 ,13 ,6 ,2 ,11 ,15 ,12 ,9 ,7 ,3 ,10 ,5 ,0},
      {15 ,12 ,8 ,2 ,4 ,9 ,1 ,7 ,5 ,11 ,3 ,14 ,10 ,0 ,6 ,13} 
   };

   short sbox1[][16]= {
      {15 ,1 ,8 ,14 ,6 ,11 ,3 ,4 ,9 ,7 ,2 ,13 ,12 ,0 ,5 ,10},
      {3 ,13 ,4 ,7 ,15 ,2 ,8 ,14 ,12 ,0 ,1 ,10 ,6 ,9 ,11 ,5},
      {0 ,14 ,7 ,11 ,10 ,4 ,13 ,1 ,5 ,8 ,12 ,6 ,9 ,3 ,2 ,15},
      {13 ,8 ,10 ,1 ,3 ,15 ,4 ,2 ,11 ,6 ,7 ,12 ,0 ,5 ,14 ,9}
   };

   short sbox2[][16]= {
      {10 ,0 ,9 ,14 ,6 ,3 ,15 ,5 ,1 ,13 ,12 ,7 ,11 ,4 ,2 ,8},
      {13 ,7 ,0 ,9 ,3 ,4 ,6 ,10 ,2 ,8 ,5 ,14 ,12 ,11 ,15 ,1},
      {13 ,6 ,4 ,9 ,8 ,15 ,3 ,0 ,11 ,1 ,2 ,12 ,5 ,10 ,14 ,7},
      {1 ,10 ,13 ,0 ,6 ,9 ,8 ,7 ,4 ,15 ,14 ,3 ,11 ,5 ,2 ,12}
   };

   short sbox3[][16]= {
      {7 ,13 ,14 ,3 ,0 ,6 ,9 ,10 ,1 ,2 ,8 ,5 ,11 ,12 ,4 ,15},
      {13 ,8 ,11 ,5 ,6 ,15 ,0 ,3 ,4 ,7 ,2 ,12 ,1 ,10 ,14 ,9},
      {10 ,6 ,9 ,0 ,12 ,11 ,7 ,13 ,15 ,1 ,3 ,14 ,5 ,2 ,8 ,4},
      {3 ,15 ,0 ,6 ,10 ,1 ,13 ,8 ,9 ,4 ,5 ,11 ,12 ,7 ,2 ,14}
   };

   short sbox4[][16]= {
      {2 ,12 ,4 ,1 ,7 ,10 ,11 ,6 ,8 ,5 ,3 ,15 ,13 ,0 ,14 ,9},
      {14 ,11 ,2 ,12 ,4 ,7 ,13 ,1 ,5 ,0 ,15 ,10 ,3 ,9 ,8 ,6},
      {4 ,2 ,1 ,11 ,10 ,13 ,7 ,8 ,15 ,9 ,12 ,5 ,6 ,3 ,0 ,14},
      {11 ,8 ,12 ,7 ,1 ,14 ,2 ,13 ,6 ,15 ,0 ,9 ,10 ,4 ,5 ,3}
   };

   short sbox5[][16]= {
      {12 ,1 ,10 ,15 ,9 ,2 ,6 ,8 ,0 ,13 ,3 ,4 ,14 ,7 ,5 ,11},
      {10 ,15 ,4 ,2 ,7 ,12 ,9 ,5 ,6 ,1 ,13 ,14 ,0 ,11 ,3 ,8},
      {9 ,14 ,15 ,5 ,2 ,8 ,12 ,3 ,7 ,0 ,4 ,10 ,1 ,13 ,11 ,6},
      {4 ,3 ,2 ,12 ,9 ,5 ,15 ,10 ,11 ,14 ,1 ,7 ,6 ,0 ,8 ,13}
   };

   short sbox6[][16]= {
      {4 ,11 ,2 ,14 ,15 ,0 ,8 ,13 ,3 ,12 ,9 ,7 ,5 ,10 ,6 ,1},
      {13 ,0 ,11 ,7 ,4 ,9 ,1 ,10 ,14 ,3 ,5 ,12 ,2 ,15 ,8 ,6},
      {1 ,4 ,11 ,13 ,12 ,3 ,7 ,14 ,10 ,15 ,6 ,8 ,0 ,5 ,9 ,2},
      {6 ,11 ,13 ,8 ,1 ,4 ,10 ,7 ,9 ,5 ,0 ,15 ,14 ,2 ,3 ,12}
   };

   short sbox7[][16]= {
      {13 ,2 ,8 ,4 ,6 ,15 ,11 ,1 ,10 ,9 ,3 ,14 ,5 ,0 ,12 ,7},
      {1 ,15 ,13 ,8 ,10 ,3 ,7 ,4 ,12 ,5 ,6 ,11 ,0 ,14 ,9 ,2},
      {7 ,11 ,4 ,1 ,9 ,12 ,14 ,2 ,0 ,6 ,10 ,13 ,15 ,3 ,5 ,8},
      {2 ,1 ,14 ,7 ,4 ,10 ,8 ,13 ,15 ,12 ,9 ,0 ,3 ,5 ,6 ,11}
   };

   uint64_t
      permute( uint64_t m, short arr[] , int q)
      {
         uint64_t n = 0;

         for( int i = 0; i < q; i++)
         {
            n = n | ( (m >> arr[i] ) & 0x1);
            n = n << 1;
         }
         return n;
      }

   uint64_t Lmask = 0xFFFFFFFF00000000;
   uint64_t Rmask = 0x00000000FFFFFFFF;

   void
      LR( uint64_t in, uint32_t& L, uint32_t& R )
      {
         L = (in & Lmask) >> 32;
         R = (in & Rmask);
      }

   uint64_t
      unLR( uint32_t L, uint32_t R )
      {
         uint64_t ret = L;
         ret = ret << 32;
         ret = ret | R;

         return ret; 
      }

   uint64_t kLmask = 0xFFFFFFFF00000000;
   uint64_t kRmask = 0x00000000FFFFFFFF;

   void
      kLR( uint64_t in, uint32_t& L, uint32_t& R )
      {
         L = (in & kLmask) >> 28;
         R = (in & kRmask);
      }

   uint64_t
      unkLR( uint32_t L, uint32_t R )
      {
         uint64_t ret = L;
         ret = ret << 28;
         ret = ret | R;

         return ret; 
      }

   short
      s_box( short index, int box)
      {
         short row;
         short col = (index >> 1) & 0xF;

         if( (index & 0x1) == 1 )
            row = (index >> 4) | 0x1;
         else
            row = (index >> 4) & 0x2;

         switch( box ){
            case 0:
               return sbox0[row][col];
            case 1:
               return sbox1[row][col];
            case 2:
               return sbox2[row][col];
            case 3:
               return sbox3[row][col];
            case 4:
               return sbox4[row][col];
            case 5:
               return sbox5[row][col];
            case 6:
               return sbox6[row][col];
            case 7:
               return sbox7[row][col];
         }
         fprintf(stderr,"KEYERROR");
         return 0;
      }


   void
      sb_expand( uint64_t S , uint8_t b[] )
      {
         uint8_t Smask = 0x3F;

         for( int i = 7; i >= 0 ; i--)
         {
            b[i] =  S & Smask;
            S = S >> 6;
         }
      }

   uint32_t
      fFunction( uint32_t R, uint64_t key)
      {
         union {
            uint64_t s;
            uint8_t b[8];
         } exp;

         uint64_t expR = permute(R, E, 64);

         expR = expR ^ key;

         sb_expand( expR, exp.b );

         uint64_t Cstr = 0;

         for( int i = 0; i < 8; i++)
         {
            Cstr = Cstr | s_box( exp.b[i], i);
            Cstr = Cstr << 4;
         }

         return permute( Cstr, PC, 32);

      }

   uint64_t
      round( uint64_t m, uint64_t key)
      {
         uint32_t L,R,C;
         LR( m , L , R );

         C = fFunction( R, key );

         C = C ^ L;

         return unLR( R, C );
      }

   uint64_t 
      keygen( uint64_t key , int round )
      {
         uint32_t L,R;
         short temp;
         short mask;
         short shift = rotation[round];

         kLR( key , L ,R);

         // I like this line
         // if shift = 2 -> mask 3 = 11b = 2 | 1
         // if shift = 1 -> mask 1 = 01b = 1 | 1
         mask = shift | 0x1;
         mask = mask << (32-shift);

         temp = L & mask;
         L = L << shift;
         L = L | temp;

         temp = R & mask;
         R = R << shift;
         R = R | temp;

         return unkLR( L, R );
      }


   uint64_t
      encrypt( uint64_t m , uint64_t key)
      {
         uint32_t kL, kR;

         //perform Inital PErmutation
         m= permute( m,IP,64);

         //Perform Inital Key Permutation
         kL = permute(key, PC1Left, 28 );
         kR = permute(key, PC1Right, 28 );
         key = unkLR( kL, kR );

         //Perform 16 rounds DES
         for( int i = 0; i < 16; i++)
         {
            key = keygen(key, i);
            m = round( m, permute(key, PC2, 48));
         }

         //undo Inital PErmutation
         m = permute( m,IPinv,64);

         return m;
      }

   uint64_t
      decrypt( uint64_t m , uint64_t key)
      {
         uint32_t kL, kR;
         uint64_t keyarr[16];

         //perform Inital PErmutation
         m= permute( m,IP,64);

         //Perform Inital Key Permutation
         kL = permute(key, PC1Left, 28 );
         kR = permute(key, PC1Right, 28 );
         key = unkLR( kL, kR );

         //Pregenerate Keys
         for( int i = 0; i < 16; i++)
         {
            keyarr[i] = keygen( key, i);
         }

         //Perform 16 rounds DES
         for( int i = 0; i < 16; i++)
         {
            m = round( m, permute(keyarr[(15-i)], PC2, 48));
         }

         //undo Inital PErmutation
         m = permute( m,IPinv,64);

         return m;
      }

   uint64_t
      getKey( char * str )
      {
         try{
            return std::stoi( str, NULL, 16);
         } catch( const std::exception& e){
            fprintf( stderr, "PROBLEM INTERPRETING KEY" );
            exit( -1 );
         } 
      }
}
