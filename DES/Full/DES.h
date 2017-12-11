#ifndef _DES_H
#define _DES_H

#include <stdint.h>
namespace DES
{
   extern short IP[];
   extern short IPinv[];

   enum SBOX{
      SBOX1 = 0,
      SBOX2,
      SBOX3,
      SBOX4,
      SBOX5,
      SBOX6,
      SBOX7,
      SBOX8,
   };

   uint64_t
      permute( uint64_t , short[] , int);

   void
      LR( uint64_t, uint32_t&, uint32_t& );

   uint64_t
      unLR( uint32_t , uint32_t );

   void
      kLR( uint64_t , uint32_t& , uint32_t&  );

   uint64_t
      unkLR( uint32_t , uint32_t  );

   short
      s_box( short , int );

   uint32_t
      fFunction( uint32_t, uint64_t);

   void
      sb_expand( uint64_t , uint8_t[] );

   uint64_t
      round( uint64_t m, uint64_t key);

   uint64_t
      encrypt( uint64_t m , uint64_t key);

   uint64_t
      decrypt( uint64_t m , uint64_t key);

   uint64_t
      getKey( char * str );
}
#endif 
