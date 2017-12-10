#ifndef CRYPTOMATH_H
#define CRYPTOMATH_H

#include <gmpxx.h>
#include <vector>


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

    /*
         GMP implementation of Fermats factorization method. Functions
         by expressing the first argument as the diffrence of squares.
         n = x^2 + y ^2 = (x+y)(x-y)
         Finds two factors and returns them.

         places the return values in the second and third arguments.

     */
    bool
            factor_fermat( mpz_t, mpz_t, mpz_t);


    /*
       Helper function for factor_fermat()
       Returns true f the first argument is a perfect square.
       false otherwise.
     */
    bool
            is_square( mpz_t );

    /*
       GMP implementation of the Pollard Rho factorizaion method.
      Initializes all return values

      finds a factor of the first argument.
      places the factor in the second argument
      returns true if a factor was found, false otherwise.
     */
    bool
            factor_PollardRho( mpz_t, mpz_t);

    /*
       GMP implementation of the Pollard p - 1 factorizaion method.
       Uses the Wheel of Sundaram to generate smooth primes.
       Initializes all return values

NOTE: WHEEL OF SUNDARM IMPLEMENTAION USES SIZE_T NOT MPZ_T.
DUE TO THIS THIS FUNCTION WILL (probably fail earlier or just never complete)
NECESSARILY FAIL IF THE FIRST ARGUMENT IS GREATER THAN
(2^64)^3 
   = 6277101735386680763835789423207666416102355444464034512896 
   = 6.2 * 10 ^ 57
   = 2^192

       finds a factor of the first argument.
       places the factor in the second argument
       returns true if a factor was found, false otherwise.
     */
    bool
       factor_Pollardp1( mpz_t, mpz_t);

    /*
       Attempts to create a smoothness bound for Pollard p-1 factorization
       in actually just calculates the 3rd root of the second argument and 
       returns it.
       This was done because research indicated that this sort of bound would
       provide a good balence between efficentcy and the algorithm working

       places the return value in the first argument
     */
    void
       smoothness( mpz_t, mpz_t);

    /*
       Helper function for Pollard p - 1
       Given n, finds the largest k st
       m^k < n. And returns m.
       Initializes all return values

       Second Argument m
       Third Arguemtn n

       places the return value in the first argument
     */
    void
       lastFactor( mpz_t, mpz_t, mpz_t);

    /*
       Finds and returns a list of primes up to twice the first argument.

       places the return value as a vector in the second argument.
     */
    void 
       Sundaram( size_t , std::vector<size_t>&);

    /*
       A GMP implemention of Shanks Square forms factoriztion Method
       64bit integer version of this code found:
https://en.wikipedia.org/wiki/Shanks%27_square_forms_factorization 
Initializes all return values

Finds a factor of the second argument using Shanks square method

places the return value in the first argument
     */
    void
       shanks_square( mpz_t , mpz_t )

       /*
          Computes the Euler Totent function on the second element
          The Totent Function is the number of numbers less than n 
          such that gcd(n m) = 1
          Initializes all return values

          places the return value in the first argument
        */
       void
       EulerTotent(  mpz_t, mpz_t );

    /*
       Returns true if the first element is a primitive root mod 
       the second element

       False otherwise
     */
    bool
       is_Generator( mpz_t, mpz_t );

}

#endif //CRYPTOMATH_H
