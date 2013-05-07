//
//  main.c
//  Eratosthenes
//
//  Created by Akhil Verghese on 5/5/13.
//  Copyright (c) 2013 Akhil Verghese. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long bit_sieve(unsigned char* primes, long long n, long long sqrt)
{
    long long noofprimes=1;
    unsigned char powers[]={1,2,4,8,16,32,64,128};
    for(long long i=3;i<=sqrt;i++)
    {
        if(!(primes[i/8]&powers[(i&7)]))
        {
            noofprimes++;
            long long p=(i*i);
            while(p<=n)
            {
                primes[p/8]|=(char)powers[p&7];
                p+=(i*2);
            }
        }
    }
    
    for(long long i=sqrt+1;i<=n;i++)
    {
        if(!(primes[i/8]&powers[(i&7)]))
        {
            noofprimes++;
        }
    }
    
    return noofprimes;
}

long long byte_sieve(char* primes, long long n, long long sqrt)
{
    long long noofprimes=1;
    for(long long i=3;i<=sqrt;i++)
    {
        if(!primes[i])
        {
            noofprimes++;
            long long p=(i*i);
            while(p<=n)
            {
                primes[p]=1;
                p+=(i*2);
            }
        }
    }
    
    for(long long i=sqrt+1;i<=n;i++)
    {
        if(!primes[i])
        {
            noofprimes++;
        }
    }
    
    return noofprimes;
}

long long diff_sieve(char* primes, long long n, long long sqrt, long long noofprimes)
{
    int* difference = malloc(noofprimes*sizeof(int));
    long long lastprime = 2,q = 0;
    for(long long i=3; i<=sqrt; i++)
    {
        if(primes[i]==0)
        {
            long long p = (i*i);
            difference[q] = (int)(i-lastprime);
            lastprime = i;
            q++;
            while(p<=n)
            {
                primes[p] = 1;
                p += (i*2);
            }
            
        }
    }
    
    for(long long i = sqrt + 1; i <= n; i++)
    {
        if(primes[i] == 0)
        {
            difference[q] = (int)(i-lastprime);
            lastprime = i;
            q++;
        }
    }
    
    return (noofprimes*8);
}


int main(int argc, const char * argv[])
{
    
    long long N,square_root;
    long long space_using_bits,space_using_difference,noofprimes;
    printf("Enter N: ");
    scanf ("%lld",&N);
    unsigned char* bit_primes=malloc(((N/8)+1)*sizeof(char));
    char* byte_primes=malloc(N*sizeof(char));
    char* diff_primes=malloc(N*sizeof(char));
    
    for(long i=0;i<(N/8)+1;i++)
        bit_primes[i]=0;
    
    int p=4;
    unsigned char powers[]={1,2,4,8,16,32,64,128};
    
    while(p<=N)
    {
        bit_primes[p/8]|=(char)powers[p&7];
        p+=2;
    }
    
    for(long i=0;i<N;i++)
    {
        byte_primes[i]=0;
        diff_primes[i]=0;
    }
    
    for(long i=4;i<N;i+=2)
    {
        byte_primes[i]=1;
        diff_primes[i]=1;
    }
    square_root=sqrt(N);
    space_using_bits=N;
    
    clock_t t_bytes=clock();
    noofprimes=byte_sieve(byte_primes,N,square_root);
    t_bytes=clock()-t_bytes;
    
    clock_t t_bits=clock();
    noofprimes=bit_sieve(bit_primes,N,square_root);
    t_bits=clock()-t_bits;
    
    clock_t t_difference=clock();
    space_using_difference=diff_sieve(diff_primes,N,square_root,noofprimes);
    t_difference=clock()-t_difference;
    
    printf("\nCalculated %lld primes",noofprimes);
    printf("\nTime taken using bits method = %.2lf",(double)t_bits/CLOCKS_PER_SEC);
    printf("\nSpace taken using bits method = %lld",space_using_bits);
    printf("\nTime taken using bytes method = %.2lf",(double)t_bytes/CLOCKS_PER_SEC);
    printf("\nSpace taken using bytes method = %lld",space_using_bits*8);
    printf("\nTime taken using difference method = %.2lf",(double)t_difference/CLOCKS_PER_SEC);
    printf("\nSpace taken using difference method = %lld",space_using_difference);
    
    free(bit_primes);
    free(diff_primes);
    return 0;
}

