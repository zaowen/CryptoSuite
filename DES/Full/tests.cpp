#include "gtest/gtest.h"
#include "DES.h"


namespace {

   TEST( PERMUTETest, func ) {
      uint64_t j = 0x1234567890ABCDE;
      uint64_t k = j;

      k = DES::permute(k,DES::IP,64);

      k = DES::permute(k,DES::IPinv,64);
      EXPECT_EQ( k , j);
   }
   TEST( SBEXPANDTest, func ) {
      uint64_t k = 0x420C41461C8;
      uint8_t b[8] = {0};

      DES::sb_expand(k,b);
      for(int i = 1 ; i < 9; i++)
      {
         EXPECT_EQ( i, b[i-1]);
      }
   }

   TEST( SBOX1Test, func ) {
      EXPECT_EQ( 3 , DES::s_box( 9 , 2 ) );
   }
   TEST( SBOX2Test, func ) {
      EXPECT_EQ( 11 , DES::s_box( 27 , 5 ) );
   }
   TEST( SBOX3Test, func ) {
      EXPECT_EQ( 5 , DES::s_box( 58 , 7-1 ) );
   }
}  // namespace

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
