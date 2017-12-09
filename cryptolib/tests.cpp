#include "cryptomath.h"
#include "gtest/gtest.h"

#include <gmpxx.h>

namespace {

   TEST(GCDTest, Basic ) {
      mpz_t a,b,g;

      mpz_init(a);
      mpz_init(b);
      mpz_init(g);

      mpz_set_ui(a, 5);
      mpz_set_ui(b, 9);

      crypto::gcd(g,a,b);
      EXPECT_EQ( 1, mpz_get_ui(g) );
   }

   TEST(GCDTest, BigIntLittleInt ) {
      mpz_t a,b,g;
      mpz_init_set_str( a, "618970019642690137449562111" , 10);
      mpz_init_set_str( b, "2" , 10);
      crypto::gcd(g,a,b);
      EXPECT_EQ( 1, mpz_get_ui(g) );
   }

   TEST(GCDTest, BigInts ) {
      mpz_t a,b,g;

      mpz_init(g);
      mpz_init_set_str( a, "162259276829213363391578010288127" , 10);
      mpz_init_set_str( b, "170141183460469231731687303715884105727" , 10);
      crypto::gcd(g,a,b);
      EXPECT_EQ( 1, mpz_get_ui(g) );
   }

   TEST(EGCDTest, Basic ) {
      mpz_t a, b, d, x, y;

      mpz_init_set_ui( a, 10);
      mpz_init_set_ui( b, 21);

      crypto::extendedGCD( d, a, b, x, y);

      EXPECT_EQ( 1, mpz_get_si(d) );
      EXPECT_EQ( -2, mpz_get_si(x) );
      EXPECT_EQ( 1, mpz_get_si(y) );
   }

   TEST(EGCDTest, BigInts ) {
      mpz_t a, b, d, x, y;
      mpz_t a1, b1;

      //Solved using Wolfram-Alpha
      mpz_init_set_str( a, "162259276829213363391578010288127" , 10);
      mpz_init_set_str( b, "170141183460469231731687303715884105727" , 10);

      mpz_init_set_str( a1, "159704011408732424717963697831805" , 10);
      mpz_init_set_str( b1, "-170141183460469231731687303715884105727" , 10);

      crypto::extendedGCD( d, a, b, x, y);

      EXPECT_EQ( 1, mpz_get_si(d) );
      EXPECT_TRUE( mpz_cmp(a1, x) );
      EXPECT_TRUE( mpz_cmp(b1, y) );
   }

   TEST( MODINVERSETest, Basic ){
      mpz_t a, x, n;

      mpz_init_set_ui( a, 10);
      mpz_init_set_ui( n, 17);

      EXPECT_TRUE( crypto::findModInverse( x, a ,n) );
      EXPECT_EQ( 12, mpz_get_si(x) );

   }

   TEST( FERMATest, Large){
      mpz_t a;
      mpz_init_set_str( a, "162259276829213363391578010288127" , 10);

      EXPECT_TRUE( crypto::isPrime_Fermat( a ) );
   }

   TEST( FERMATest, Basic){
      mpz_t a;
      mpz_init_set_ui( a, 11 );

      EXPECT_TRUE( crypto::isPrime_Fermat( a ) );
   }

   TEST( FERMATest, BasicFalse ){
      mpz_t a;
      mpz_init_set_ui( a, 100 );

      EXPECT_FALSE( crypto::isPrime_Fermat( a ) );
   }

   TEST( FERMATFACTORTest, Base){
      mpz_t a,p,q;
      mpz_init( a );
      mpz_set_ui(a, 295927);

      crypto::factor_fermat( a, p, q);
      EXPECT_EQ( 547, mpz_get_si(p) );
      EXPECT_EQ( 541, mpz_get_si(q) );

   }

   TEST( POLLARDRHOFACTORTest, Base){
      mpz_t a,d;
      mpz_init( a );
      mpz_set_ui(a, 8051);

      crypto::factor_PollardRho( a, d);
      EXPECT_EQ( 97, mpz_get_si(d) );
   }

   TEST( POLLARDP1FACTORTest, Base){
      mpz_t a,d;
      mpz_init( a );
      mpz_set_ui(a, 299);

      crypto::factor_Pollardp1( a, d);
      EXPECT_EQ( 13, mpz_get_si(d) );
   }

   /*
      TEST( QUADSEIVETest, Base){
      size_t n;
      size_t d = crypto::Quadratic_Seive( n );
      EXPECT_EQ( 1093, d );
      }
    */

   TEST( EULERTOTENTest, Base1){
      mpz_t m, n;
      mpz_init( n );
      mpz_set_ui(n,89);
      crypto::EulerTotent( m,n);
      EXPECT_EQ( 88, mpz_get_ui(m) );
   }

   TEST( EULERTOTENTest, Base2){
      mpz_t m, n;
      mpz_init(n);
      mpz_set_ui(n,54);
      crypto::EulerTotent( m,n);
      EXPECT_EQ( 18, mpz_get_ui(m) );
   }

   TEST( GENERATORTest, Base1){
      mpz_t m, n;
      mpz_init_set_ui(n,43);
      mpz_init_set_ui(m,33);
      EXPECT_TRUE( crypto::is_Generator( m, n ) );
   }

   TEST( GENERATORTest, Base2){
      mpz_t m, n;
      mpz_init_set_ui(n,54);
      mpz_init_set_ui(m,5);
      EXPECT_TRUE( crypto::is_Generator( m, n ) );
   }

}  // namespace

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
