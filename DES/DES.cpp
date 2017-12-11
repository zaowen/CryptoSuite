#include "DES.h"
#include <stdio.h>

namespace DES
{

   short sbox1[][8] = 
   {
      {5,2,1,6,3,4,7,0},
      {1,4,6,2,0,7,5,3}
   };

   short sbox2[][8] =
   {
      {4,0,6,5,7,1,3,2},
      {5,3,0,7,6,2,1,4}
   };

   short mask12 = 0x30;
   short mask3 =  0x08;
   short mask4 =  0x04;
   short mask56 = 0x03;

   short
      expand( short e )
      {
         short b12 = ( e & mask12 ) >> 4;
         short b4 =  ( e & mask4 ) >> 2 ;
         short b3 =  ( e & mask3 ) >> 3;
         short b56 = ( e & mask56 );

         return (b12 << 6) | (b4 << 5) | (b3 << 4) | (b4 << 3) | (b3 << 2) | (b56);
      }

   short sbr_mask = 0x8;
   short sbc_mask = 0x7;

   short
      s_box( short index , SBOX box )
      {
         short row = ( index & sbr_mask ) >> 3;
         short col = ( index & sbc_mask );

         if( box == SBOX1 )
         {
            return sbox1[row][col];
         }
         else if (box == SBOX2)
         {
            return sbox2[row][col];
         }
         else
         {
            fprintf(stderr,"SBOXERROR\n");
            return 0;
         }

      }

   uint16_t
      round( uint16_t lr, uint16_t K , int round )
      {
         short L,R;
         short fR;
         uint32_t pK;
         LR( lr, L, R );
         pK = prepKey(K);
         fR = fFunction( R, rotKey( pK, round) );

         return unLR(R, fR ^ L);
      }

   short
      fFunction( short R, uint16_t K )
      {
         short sl,sr;
         R = expand(R);
         R = R ^ K;
         sboxLR( R, sl, sr );
         sl = s_box(sl, SBOX1);
         sr = s_box(sr, SBOX2);
         return unsboxLR( sl, sr);

      }

   uint16_t Lmask = 0xFC0;
   uint16_t Rmask = 0x03F;
   void
      LR( uint16_t in, short& L, short& R )
      {
         L = (in & Lmask) >> 6;
         R = (in & Rmask);
      }

   uint16_t
      unLR( short L , short R )
      {
         uint16_t ret;
         ret = L & 0x3F;
         ret = ret << 6;
         R = R & 0x3F;
         ret = ret | R;
         return ret;
      }

   short sLmask = 0xF0;
   short sRmask = 0x0F;
   void 
      sboxLR( short in, short& L, short& R )
      {
         L = (in & sLmask) >> 4;
         R = (in & sRmask);
      }

   short
      unsboxLR( short L , short R )
      {
         return ( L << 4 ) | ( R );
      }

   short
      rotKey( uint32_t k , int round )
      {
         k = k >> (10 - round);
         return k & 0xFF;
      }

   uint32_t
      prepKey( uint16_t k )
      {
         uint32_t pk;
         pk = k & 0x1FF;
         pk = pk << 9;
         pk = pk | k;
         return pk;
      }
}
