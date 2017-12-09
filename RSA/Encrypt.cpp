#include <stdio.h>
#include <gmpxx.h>
#include "cryptomath.h"

int getkey( FILE* f ,size_t &k, mpz_t e, mpz_t n  ){

        if(f == NULL )
        {
                return 1;
        }

        mpz_inits(e,n,NULL);

        fscanf(f, "%ld" , &k);
        mpz_inp_str(e , f, 16);
        mpz_inp_str(n , f, 16);

        return 0;
}

void encrypt( mpz_t m, mpz_t c, mpz_t e, mpz_t n , size_t k, void* ptr){
        mpz_import(m,k/8,1,1,1,0, ptr);
        mpz_powm_sec(c,m,e,n);
}
int main( int argc, char* argv[]){
        mpz_t e, n;
        size_t k = 0;

        FILE* keyfile;

        if( argc >= 2 )
        {

                keyfile = fopen( argv[1], "r" );

                if( getkey( keyfile , k , e , n))
                {
                        return -1;
                }

                mpz_t m ,c;

                mpz_inits(m,c,NULL);

                char ptr[k/8+1];
                size_t result = fread( ptr , 1, k/8 , stdin);

                while( result ){
                        //fwrite
                        encrypt(m,c,e,n,k,ptr);
                        mpz_out_str( stdout,16, c );
                        printf("\n");
                        result = fread( ptr , 1, k/8 , stdin);
                }
        }
}
