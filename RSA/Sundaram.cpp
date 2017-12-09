#include <stdio.h>
#include <stdlib.h>

int main()
{
        size_t n,r;
        char *arr;

        scanf("%lu" , &n);

        arr  = (char*)calloc( n, 1);

        for( size_t i= 1; i < n; i++)
                for( size_t j= 1; j < i; j++)
                {
                        r = i + j + 2*i*j;
                        if(r < n)
                                arr[n] = 1;
                }
        printf("2,");
        for( size_t i= 1; i < n; i++)
        {
                if( !arr[i])
                {
                        printf("%lu,", i*2 + 1);
                }
        }
}
