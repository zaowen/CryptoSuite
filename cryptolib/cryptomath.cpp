#include "cryptomath.h"

namespace crypto
{
    void
        gcd( mpz_t g, mpz_t a, mpz_t b)
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

            mpz_init(q);
            mpz_init(rop);
            mpz_init(sub);

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

    bool
        isPrime_Fermat( mpz_t n )
        {
            mpz_t a;

            gmp_randinit();

            mpz_rrandomb( a,
        }
}
