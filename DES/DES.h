#ifndef _DES_H_
#define _DES_H_

#include <stdint.h>

namespace DES
{

   enum SBOX{
      SBOX1,
      SBOX2
   };

   /*
      Performs the simplified DES expand function
      (123456) -> (12434356)
    */
   short
      expand( short );

   /*
      Runs an input through an s-box.
      S-boxes are 2 by 8 and indexing is performed as follows
      The first two bits determine the row
      the next 4 determine the column
    */
   short
      s_box( short , SBOX );

   /*
      Upper Level DES operation.Performs one full SDES round.
   */
   uint16_t
      round( uint16_t, uint16_t, int );

   /*

    */
   short
      fFunction( short, uint16_t );

   /*
      Seperates an input into the 6 left and right bits.
      For input into the f(R,K)
   */
   void
      LR( uint16_t, short&, short& );

   /*
      Conjoins two 6 bit numbers into a single 12 bit word
   */
   uint16_t
      unLR( short, short );

   /*
      Seperates an input into the 4 left and right bits.
      For input into the s-boxes
   */
   void 
      sboxLR( short, short&, short& );

   /*
   */
   short
      unsboxLR( short L , short R );

   /*
   */
   short
      rotKey( uint32_t, int );

   uint32_t
      prepKey( uint16_t );

}

#endif
