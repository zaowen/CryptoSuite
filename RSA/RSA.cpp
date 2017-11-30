#include <iostream>

#include <gmpxx.h>
#include "cryptomath.h"

void chooseE( mpz_t e, mpz_t totent )
{
    mpz_t g;

    crypto::random_prime( e , 17 );
    crypto::gcd(g, e, totent );

    while( mpz_cmp_si( g, 1) != 0 )
    {
        mpz_add_ui(e, e, 1);
    }

    return;
}

int main()
{
    mpz_t p, q, n;
    mpz_t p1, q1,totent; // p-1, q-1
    mpz_t e,d;

    mpz_inits( n, p1,q1,totent, NULL );

    crypto::random_prime( p, 500 );
    crypto::random_prime( q, 500 );

    mpz_sub_ui( p1 , p , 1);
    mpz_sub_ui( q1 , q , 1);

    mpz_mul( n , p , q );

    crypto::lcm( totent, p1, q1);

    chooseE( e, totent);

    crypto::findModInverse( d, e, totent);

    gmp_printf( "Public key:%Zd", e);
    gmp_printf( "Private key:%Zd", d);

}

