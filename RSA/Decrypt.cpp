#include <stdio.h>
#include <gmpxx.h>
#include "cryptomath.h"

int getkey( FILE* f ,size_t &k, mpz_t d, mpz_t n  ){

        if(f == NULL )
        {
                return 1;
        }

        mpz_inits(d,n,NULL);

        fscanf(f, "%ld" , &k);
        mpz_inp_str(d , f, 16);
        mpz_inp_str(n , f, 16);
        mpz_inp_str(d , f, 16);

        return 0;
}

void decrypt( mpz_t c, mpz_t m, mpz_t d, mpz_t n){
        mpz_powm_sec(m,c,d,n);
}

int main( int argc, char* argv[]){
        mpz_t d, n;
        size_t k = 0;

        FILE* keyfile;

        if( argc >= 2 )
        {

                keyfile = fopen( argv[1], "r" );

                if( getkey( keyfile , k , d , n))
                {
                        return -1;
                }


                mpz_t m ,c;

                mpz_inits(m,c,NULL);

                char ptr[k/8+1];
                size_t result = mpz_inp_str( c,stdin, 16);

                while( result ){
                        decrypt(c,m,d,n);
                        mpz_export(ptr,NULL,1,k/8,1,0, m);
                        fwrite( ptr, 1, k/8, stdout);
                        result = mpz_inp_str( c,stdin, 16);
                }
        }
}
