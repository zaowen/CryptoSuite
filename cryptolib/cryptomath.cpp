#include "cryptomath.h"
#include <inttypes.h>
#include <math.h>
#include <ctime>

namespace crypto
{

   bool _RAND_INIT_ = false;
   gmp_randstate_t _R_STATE;

   void
      TESTRAND()
      {
      gmp_randinit_default (_R_STATE);
      gmp_randseed_ui(_R_STATE, 101092 );

      _RAND_INIT_ = true;
      }

   void
      gcd( mpz_t g, mpz_t a, mpz_t b)
      {
         mpz_t c,d;
         mpz_inits(g,c,d,NULL);
         mpz_set( c, a);
         mpz_set( d, b);

         _GCD( g, c ,d);

      }

   void
      lcm( mpz_t l, mpz_t a, mpz_t b)
      {
         mpz_t g,ab,g2;

         gcd( g, a, b);

         mpz_inits(g2,l,ab,NULL);

         mpz_mul(ab ,a ,b);
         mpz_mul(g2 ,g ,g);
         mpz_tdiv_q(l ,ab ,g);
      }

   void
      _GCD( mpz_t g, mpz_t a, mpz_t b )
      {
         mpz_t r; //remainder
         mpz_init(r);
         while( mpz_cmp_si( b , 0 ) ){
            mpz_mod( r, a, b); //r = a % b
            mpz_swap(a , b);
            mpz_swap(b , r);
         }
         mpz_swap( g , a);
         return;
      }

   void
      extendedGCD( mpz_t d, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
      {
         if( mpz_cmp_si( a , 0) == 0 ) // if ( a== 0 )
         {
            mpz_init_set_si( x, 0 ); // x = 0
            mpz_init_set_si( y, 1 ); // y = 1

            mpz_init_set(d, b);  // return b
            return;
         }

         mpz_t x1, y1;
         mpz_t m;

         mpz_init(m);
         mpz_mod( m, b ,a);
         extendedGCD(d, m , a, x1, y1 );

         mpz_t q,rop,sub;
         mpz_inits(q, rop, sub, NULL);

         // x = y1 - (b/a) * x1
         mpz_tdiv_q(q ,b ,a); // q = (b/a)
         mpz_mul(rop ,q ,x1); // (b/a) * x1
         mpz_sub(sub, y1, rop); // y1 - (b/a) * x1

         mpz_init_set(x , sub);
         mpz_init_set(y, x1);

         return;
      }

   bool
      findModInverse(mpz_t x, mpz_t a, mpz_t n )
      {
         mpz_t y,d;

         extendedGCD( d, a, n, x ,y );

         // Ensure answer is positive
         if( mpz_sgn(x) < 0 )
         {
            mpz_add( x , x, n );
         }

         return ! mpz_cmp_si( d, 1 );
      }

   void 
      initRand()
      {

         long int seed = static_cast<long int>(time(NULL) );

         gmp_randinit_default (_R_STATE);
         gmp_randseed_ui(_R_STATE, seed );

         _RAND_INIT_ = true;
      }

   bool
      isPrime_Fermat( mpz_t n )
      {
         if( !_RAND_INIT_ )
            initRand();

         if( mpz_divisible_ui_p(n, 2) != 0 )
            return false;

         return isPrime_Fermat( n, 5 );
      }

   bool
      isPrime_Fermat( mpz_t n, int itr )
      {

         if( !_RAND_INIT_ )
            initRand();

         if( itr == 0 )
         {
            return true;
         }

         mpz_t a;
         mpz_t mod;
         mpz_t nLess;

         mpz_init( a );
         mpz_init( mod );
         mpz_init( nLess );

         mpz_sub_ui( nLess, n, 1 ); // n-1


         mpz_urandomm( a ,_R_STATE, n );
         gcd( mod, a, n );

         if( mpz_cmp_ui( mod, 1 ) != 0 )
         {
            return false;
         }

         mpz_powm_sec( mod, a, nLess , n);

         if( mpz_cmp_ui( mod, 1 ) == 0 )
         {
            return isPrime_Fermat(n , itr -1 );
         }

         return false;
      }

   void 
      random_prime( mpz_t rop, int n)
      {
         mpz_t op1, op2, two;

         if( !_RAND_INIT_ )
            initRand();

         mpz_inits(rop,op1,op2,NULL);
         mpz_init_set_ui( two, 2 );

         mpz_pow_ui( op1, two, n);

         do{
            mpz_urandomb ( op2, _R_STATE , n);
            mpz_add( rop, op1, op2);
         }while ( !isPrime_Fermat( rop ) );

      }

   bool
      is_square(mpz_t n)
      {
         mpz_t r;
         mpz_init(r);
         return mpz_root( r, n, 2);
      }

   bool
      factor_fermat( mpz_t n , mpz_t p, mpz_t q )
      {
         mpz_t i,i2,m;
         mpz_inits(i,i2,m,p,q,NULL);

         mpz_set_ui( i , 1);

         mpz_mul( i2 , i , i);
         mpz_add( m , n , i2);

         while( !is_square( m ) ){
            mpz_add_ui( i , i , 1);
            mpz_mul( i2 , i , i);
            mpz_add( m , n , i2);
         }

         mpz_root(m, m, 2);

         mpz_add(p, m , i );
         mpz_sub(q, m , i );

         return true;
      }

   void
      smoothness( mpz_t B, mpz_t n)
      {
         mpz_root(B,n,3);
      }

   void
      lastFactor( mpz_t m, mpz_t b , mpz_t n ) {

         mpz_init(m);
         mpz_set(m , b);

         while( mpz_cmp( m , n) < 0 )
         {
            mpz_mul(m,m,b);
         }

         mpz_divexact( m, m, b );
      }

   bool
      factor_Pollardp1( mpz_t n , mpz_t g)
      {
         mpz_t M,b,a,B,m;
         std::vector<size_t> p;
         mpz_inits( M, a, g, b, B, m, NULL);
         mpz_set_ui( a, 2);
         mpz_set_ui(M,1);

         //choose a Smoothness based on n;
         smoothness(B,n);
         Sundaram( mpz_get_ui(B) , p);
         auto i = p.begin();

         while( i != p.end() )
         {
            mpz_set_ui( b, *i );
            lastFactor( m, b, n);
            mpz_mul( M, M, m);
            i++;
         }

         mpz_powm( a, a, M, n);

         mpz_sub_ui( a, a, 1 );
         gcd( g, a, n);

         if( mpz_cmp_ui(g, 1) == 0 )
         {
            return false;
         }

         if( mpz_cmp(g, n) >= 0 )
         {
            return false;
         }

         return true;
      }


   bool
      factor_PollardRho( mpz_t n, mpz_t d)
      {
         mpz_t x, y,rop;
         mpz_inits( x, y, rop, d,NULL);

         //g(x) = (x^2 +1)
         do{
            //g(x)
            mpz_mul(x,x,x);
            mpz_add_ui(x,x,1);

            //g(g(y))
            mpz_mul(y,y,y);
            mpz_add_ui(y,y,1);

            mpz_mul(y,y,y);
            mpz_add_ui(y,y,1);

            //|x-y|
            mpz_sub(rop,x,y);
            mpz_abs(rop,rop);

            gcd( d, n, rop);

         } while( mpz_cmp_ui(d, 1) == 0 );

         return mpz_cmp(d, n);
      }

   void 
      Sundaram( size_t n, std::vector<size_t> &p)
      {
         char *arr;
         size_t r;
         n = n >> 1;
         arr  = (char*)calloc( n, 1);

         for( size_t i= 1; i < n; i++)
            for( size_t j= 1; j < i; j++)
            {
               r = i + j + 2*i*j;
               if(r < n)
                  arr[r] = 1;
            }

         p.push_back(2);
         for( size_t i= 1; i < n; i++)
         {
            if( !arr[i])
            {
               p.push_back( i*2 + 1);
            }
         }
      }

#define nelems(x) (sizeof(x) / sizeof((x)[0]))

   const int multiplier[] = {1, 3, 5, 7, 11, 3*5, 3*7, 3*11, 5*7, 5*11, 7*11, 3*5*7, 3*5*11, 3*7*11, 5*7*11, 3*5*7*11};

   void 
      factor_Shank( mpz_t r, mpz_t N )
      {
         mpz_init(r);
         mpz_t D, Po, P, Pprev, Q, Qprev, q, b, s;
         mpz_t L, B, rop, one;
         mpz_inits( D, Po, P, Pprev, Q, Qprev, q, b, s, L, B,rop,one, NULL);
         uint32_t i;

         mpz_set_ui( one , 1);
         //s = (uint64_t)(sqrtl(N)+0.5);
         if( mpz_root(s, N, 2 ) )
         {
            mpz_set( r, s );
            return;
         }

         //for (int k = 0; k < nelems(multiplier) && N <= UINT64_MAX/multiplier[k]; k++) {
         for (size_t k = 0; k < nelems(multiplier); k++) {

            //D = multiplier[k]*N;
            mpz_mul_ui( D, N, multiplier[k] );

            //Po = Pprev = P = sqrtl(D);
            mpz_root( P, D, 2);
            mpz_set( Pprev, P);
            mpz_set( Po ,P );

            //Qprev = 1;
            mpz_set_ui(Qprev, 1);

            //Q = D - Po*Po;
            mpz_mul( rop, Po, Po);
            mpz_sub( Q, D, rop);

            //L = 2 * sqrtl( 2*s );
            mpz_mul( rop, s, s);
            mpz_sqrt(rop, rop);
            mpz_mul_ui( L, s, 2);


            //B = 3 * L;
            mpz_mul_ui( B, L, 3);

            //for (i = 2 ; i < B ; i++) {
            for (i = 2 ; mpz_cmp_ui( B, i ) > 0 ; i++) {

               //b = (uint64_t)((Po + P)/Q);
               mpz_add(rop, Po, P);
               mpz_tdiv_q(b, rop, Q);

               //P = b*Q - P;
               mpz_mul( rop, b, Q);
               mpz_sub( P, rop, P);


               //q = Q;
               mpz_set( q, Q );

               //Q = Qprev + b*(Pprev - P);
               mpz_sub(rop, Pprev, P);
               mpz_mul(rop, rop, b);
               mpz_add(Q, Qprev, rop);

               //r = (uint64_t)(sqrtl(Q)+0.5);
               mpz_sqrt(r, Q);

               mpz_mul(rop, r, r);
               //if (!(i & 1) && r*r == Q) break;
               if ( !(i & 1) && mpz_cmp(rop, Q) == 0) break;

               //Qprev = q;
               mpz_set( Qprev, q);

               //Pprev = P;
               mpz_set( Pprev, P);
            };

            //if (i >= B) continue;
            if ( mpz_cmp_ui( B, i ) <= 0 ) continue;

            //b = (uint64_t)((Po - P)/r);
            mpz_sub(rop, Po, P);
            mpz_tdiv_q(b, rop, r);

            //Pprev = P = b*r + P;
            mpz_mul(rop, b, r);
            mpz_add(Pprev, rop, P);
            mpz_set(P, Pprev);

            //Qprev = r;
            mpz_set( Qprev, r);

            //Q = (D - Pprev*Pprev)/Qprev;
            mpz_mul( rop, Pprev, Pprev);
            mpz_sub( rop, D, rop);
            mpz_tdiv_q( Q, rop, Qprev);

            i = 0;
            do {
               //b = (uint64_t)((Po + P)/Q);
               mpz_add(rop, Po, P);
               mpz_tdiv_q(b, rop, Q);

               //Pprev = P;
               mpz_set( Pprev, P);

               //P = b*Q - P;
               mpz_mul( rop, b, Q );
               mpz_sub( P, rop, P );

               //q = Q;
               mpz_set( q, Q);

               //Q = Qprev + b*(Pprev - P);
               mpz_sub(rop, Pprev, P);
               mpz_mul(rop, rop, b);
               mpz_add(Q, Qprev, rop);

               //Qprev = q;
               mpz_set( Qprev, q);
               i++;
            } while (mpz_cmp( P , Pprev ) != 0 );
            gcd( r, N, Qprev);
            if ( mpz_cmp_ui(r, 1) != 0 && mpz_cmp(r,N) != 0 )
               return;
         }
         mpz_set_ui(r, 0);
         return;
      }

   void
      EulerTotent( mpz_t t, mpz_t n)
      {
         mpz_t g,i;
         mpz_init_set_ui(t,1);
         mpz_init_set_ui(i, 2);

         while( mpz_cmp(i ,n ) < 0  )
         {
            gcd(g,i,n);

            if(mpz_cmp_ui( g, 1) == 0)
            {
               mpz_add_ui(t,t,1);
            }

            mpz_add_ui(i,i,1);
         }
      }

   bool
      is_Generator(mpz_t m, mpz_t n)
      {
         mpz_t phi,rop;
         std::vector<size_t> p;

         if( mpz_cmp_ui(m , 1) ==0 || mpz_cmp(m ,n) > 0 )
         {
            return false;
         }

         EulerTotent(phi,n);

         Sundaram( mpz_get_ui(phi), p );

         auto i = p.begin();

         mpz_init(rop);

         while( i != p.end())
         {
            mpz_powm_ui( rop, m, *(i++), n);
            if( mpz_cmp_ui( rop, 1 ) == 0 )
            {
               return false;
            }

         }

         return true;

      }
}
