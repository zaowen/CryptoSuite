#include "DES.h"
#include "gtest/gtest.h"


namespace {

   TEST( EXPANDTest, Book ) {
      short exp = 0x19;
      EXPECT_EQ( 0x55, DES::expand(exp) );
   }
   TEST( KEYPREPTest, Book ) {
      uint16_t key = 0x099;
      uint32_t pkey = DES::prepKey( key );

      EXPECT_EQ( 0x13299 , pkey );

   }

   TEST( KEYTest, Book ) {
      uint16_t key = 0x099;
      uint32_t pkey = DES::prepKey( key );

      EXPECT_EQ( 0x4C , DES::rotKey(pkey, 0) );
      EXPECT_EQ( 0x99 , DES::rotKey(pkey, 1) );
      EXPECT_EQ( 0x32 , DES::rotKey(pkey, 2) );
      EXPECT_EQ( 0x65 , DES::rotKey(pkey, 3) );

   }

   TEST( KEYTest2, Book ) {
      uint16_t key = 0x1ff;
      uint32_t pkey = DES::prepKey( key );

      EXPECT_EQ( 0xff , DES::rotKey(pkey, 0) );
      EXPECT_EQ( 0xff , DES::rotKey(pkey, 1) );
      EXPECT_EQ( 0xff , DES::rotKey(pkey, 2) );
      EXPECT_EQ( 0xff , DES::rotKey(pkey, 3) );

   }

   TEST( FFUNCTIONTest, Book){
      short testr = 0x26;
      uint16_t key = 0x099;
      uint32_t pkey;
      short roundKey;

      pkey = DES::prepKey(key);

      roundKey = DES::rotKey( pkey ,3);

      EXPECT_EQ( 4,  DES::fFunction( testr, roundKey ) );

   }

   TEST( ROUNDTest, Book){
      uint16_t key = 0x099;
      uint16_t m = 0x726;

      EXPECT_EQ( 2456 ,  DES::round( m, key ,3) );
   }

   TEST( FULL_ONE_Test, Mind){
      uint16_t key = 0x099;
      uint16_t m = 0x726;
      short L,R;

      //Encrypt
      m = DES::round( m, key ,0);

      DES::LR( m, L, R);
      m = DES::unLR(R,L);

      //decrypt
      m = DES::round( m, key ,0);

      DES::LR( m, L, R);
      m = DES::unLR(R,L);

      EXPECT_EQ( 0x726 ,  m );
   }

   TEST( FULL_TWO_Test, Mind){
      uint16_t m = 0xE6A;
      uint16_t k = 0x099;
      short L,R;

      uint16_t c = m;
      for( int i = 0; i < 2; i++)
      {
         c = DES::round( c, k, i );
      }

      DES::LR( c, L, R);
      c = DES::unLR(R,L);

      for( int i = 0; i < 2; i++)
      {
         c = DES::round( c, k, (1-i) );
      }

      DES::LR( c, L, R);
      c = DES::unLR(R,L);

      EXPECT_EQ( m , c );
   }

   TEST( FULL_THREE_Test, Mind){
      uint16_t m = 0xE6A;
      uint16_t k = 0x1FF;
      short L,R;

      uint16_t c = m;

      for( int i = 0; i < 3; i++)
      {
         c = DES::round( c, k, i );
      }

      DES::LR( c, L, R);
      c = DES::unLR(R,L);

      for( int i = 0; i < 3; i++)
      {
         c = DES::round( c, k, (2-i) );
      }

      DES::LR( c, L, R);
      c = DES::unLR(R,L);

      EXPECT_EQ( m , c );
   }

   TEST( FULL_FOUR_Test, Mind){
      uint16_t m = 0xE6A;
      uint16_t k = 0x10F;
      short L,R;

      uint16_t c = m;

      for( int i = 0; i < 4; i++)
      {
         c = DES::round( c, k, i );
      }

      DES::LR( c, L, R);
      c = DES::unLR(R,L);

      for( int i = 0; i < 4; i++)
      {
         c = DES::round( c, k, (3-i) );
      }

      DES::LR( c, L, R);
      c = DES::unLR(R,L);

      EXPECT_EQ( m , c );
   }


}  // namespace

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
