#include <iostream>

#include <gmpxx.h>
#include "cryptomath.h"

#define k 2048

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
    crypto::random_prime( p, k/2 );
    crypto::random_prime( q, k/2 );

    mpz_mul( n , p , q );

    //Choose e with gcd(e,(p-1)(q-1))=1
    mpz_sub_ui( p1 , p , 1);
    mpz_sub_ui( q1 , q , 1);

    mpz_mul(totent, p1, q1);

    if( !chooseE( e, totent) ){
            std::cerr << "Issue";
            return false;
    }

    crypto::findModInverse( d, e, totent);

    printf( "%d\n", k);
    mpz_out_str( stdout, 16, e);
    printf( "\n");
    mpz_out_str( stdout, 16, n);
    printf( "\n");
    mpz_out_str( stdout, 16, d);
    printf( "\n");
}

