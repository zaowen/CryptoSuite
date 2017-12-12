#ifndef _DES_H
#define _DES_H

#include <stdint.h>
namespace DES
{
   extern short IP[];
   extern short IPinv[];
   extern short E[];
   extern short PC[];
   extern short PC1Left[];
   extern short PC1Right[];
   extern short PC2[];
   extern short rotation[];
   extern short sbox0[4][16];
   extern short sbox1[4][16];
   extern short sbox2[4][16];
   extern short sbox3[4][16];
   extern short sbox4[4][16];
   extern short sbox5[4][16];
   extern short sbox6[4][16];
   extern short sbox7[4][16];

   uint64_t
      permute( uint64_t , short[] , int);

   void
      LR( uint64_t, uint32_t&, uint32_t& );

   uint64_t
      unLR( uint32_t , uint32_t );

   void
      kLR( uint64_t , uint32_t& , uint32_t& );

   uint64_t
      unkLR( uint32_t , uint32_t  );

   short
      s_box( short , int );

   uint32_t
      fFunction( uint32_t, uint64_t);

   void
      sb_expand( uint64_t , uint8_t[] );

   uint32_t
      cb_collapse( uint8_t b[] );

   uint64_t
      round( uint64_t , uint64_t);

   uint64_t
      encrypt( uint64_t , uint64_t);

   uint64_t
      decrypt( uint64_t, uint64_t );

   uint64_t
      getKey( char * );
}
#endif 
