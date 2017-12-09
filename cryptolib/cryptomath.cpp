#include "cryptomath.h"

#include <ctime>

namespace crypto
{

        bool _RAND_INIT_ = false;
        gmp_randstate_t _R_STATE;

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

                        return isPrime_Fermat( n, 3 );
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

}
