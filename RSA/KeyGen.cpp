#include <iostream>
#include <string>

#include <gmpxx.h>
#include "cryptomath.h"


bool chooseE( mpz_t e, mpz_t totent )
{
    mpz_t g;

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

bool validate_key( size_t k )
{
   return (k >= 512) && (k & 0x7 != 0);
}

int main( int argc, char* argv[])
{
    mpz_t p, q, n;
    mpz_t p1, q1,totent; // p-1, q-1
    mpz_t e,d;

   if( argc <  2 )
   {
      fprintf( stderr, "Useage:\n\t%s <key-size>\n", argv[0] );
      return -1;
   }

   size_t k = std::stoul( argv[1], nullptr, 10);

   if( validate_key(  k ) )
   {
      fprintf( stderr, "Keysize must be divisible by 8 and greater than 2^32", argv[0] );
      return -1;
   }

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

