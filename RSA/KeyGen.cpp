#include <iostream>

#include <gmpxx.h>
#include "cryptomath.h"



bool chooseE( mpz_t e, mpz_t totent )
{
    mpz_t g;

    //crypto::random_prime( e , 3 );
    mpz_init_set_ui( e, 65537 );
    crypto::gcd(g, e, totent );

    while( mpz_cmp_si( g, 1) != 0 )
    {
            if(mpz_cmp(e,totent) >= 0 )
            {
                    return false;
            }
        mpz_add_ui(e, e, 2);
    }
    return true;
}

int main()
{
    mpz_t p, q, n;
    mpz_t p1, q1,totent; // p-1, q-1
    mpz_t e,d;

    mpz_inits( n, p1,q1,totent, NULL );

    //Choose secret primes p,q
    crypto::random_prime( p, 500 );
    crypto::random_prime( q, 500 );

    mpz_mul( n , p , q );

    //Choose e with gcd(e,(p-1)(q-1))=1
    mpz_sub_ui( p1 , p , 1);
    mpz_sub_ui( q1 , q , 1);

    //crypto::lcm( totent, p1, q1);
    mpz_mul(totent, p1, q1);

    if( !chooseE( e, totent) ){
            std::cerr << "Issue";
            return false;
    }

    crypto::findModInverse( d, e, totent);

    gmp_printf( "%Zd\n%Zd\n%Zd\n", e,n,d);
    /*
    gmp_printf( "Public key:%Zd\n", e);
    gmp_printf( "Encryption n:%Zd\n", n);
    gmp_printf( "Private key:%Zd\n", d);
    */
}

