#ifndef CRYPTOMATH_H
#define CRYPTOMATH_H

#include <gmpxx.h>


namespace crypto
{

    /*
       Initalizes all return values
        stores the return value in the first argument
     */
    void
        gcd(mpz_t, mpz_t, mpz_t );

    /*
       Initalizes all return values
        stores the return value in the first argument
     */
    void
        lcm(mpz_t, mpz_t, mpz_t );

    /*
       Private function called by gcd()
       values are assumed to be valid
     */
    void
        _GCD(mpz_t, mpz_t, mpz_t );

    /*
       Solves equations of the form 1 = xa + yb

       Initalizes all return values

        stores the return value in the first argument
       returns false if no modular inverse exists
     */
    void
        extendedGCD( mpz_t, mpz_t, mpz_t, mpz_t, mpz_t);

    /*
       Solves equations of the form 1 = xa + nb
       and finds the modular inverse of a mod n

       Initalizes all return values

        stores the return value in the first argument
       returns false if no modular inverse exists
     */
    bool
        findModInverse(mpz_t, mpz_t, mpz_t );

    /*
       Checks if the arument is prime.
       Runs the Fermat Primality test 3 times.

       returns true if prime
     */
    bool
        isPrime_Fermat( mpz_t );

    /*
       Checks if the first arument is prime.
       Runs the Fermat Primality test n  times.
       where n is the second argument

       returns true if prime
     */
    bool
        isPrime_Fermat( mpz_t, int );

    /*
       Generates a random prime between 2^n -1 and 2^(n+1) - 1
       Initalizes all return values

       places the return value in the first argument
     */
    void
        random_prime( mpz_t,int );

    bool
            factor_fermat( mpz_t, mpz_t, mpz_t);

    bool
            is_square( mpz_t );

    bool
            factor_PollardRho( mpz_t, mpz_t);

    bool
            factor_Pollardp1( mpz_t, mpz_t);

    void
            chooseB( mpz_t, mpz_t);

    void
            smooth( mpz_t, mpz_t, mpz_t);
}

#endif //CRYPTOMATH_H
