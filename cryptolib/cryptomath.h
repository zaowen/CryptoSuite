#ifndef CRYPTOMATH_H
#define CRYPTOMATH_H

#include <gmpxx.h>


namespace crypto
{

void
gcd(mpz_t, mpz_t, mpz_t );

void
extendedGCD( mpz_t, mpz_t, mpz_t, mpz_t, mpz_t);

bool
findModInverse(mpz_t, mpz_t, mpz_t );

bool
    isPrime_Fermat( mpz_t );

}

#endif //CRYPTOMATH_H
