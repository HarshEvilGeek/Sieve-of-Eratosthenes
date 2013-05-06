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

char get_bitvalue(unsigned char a, int n)//returns value of nth bit
{
    if(a&(char)pow(2,n))
        return 1;
    else
        return 0;
}

unsigned char set_bitvalue(unsigned char a,int n)//sets nth bit as one
{
    return a|=(char)pow(2,n);
}

long long bit_sieve(unsigned char* primes, long long n, long long sqrt)
{
    long long noofprimes=0;
    for(long long i=2;i<=sqrt;i++)
    {
        if(get_bitvalue(primes[i/8], (i%8))==0)
        {
            noofprimes++;
            long long p=(i*i);
            if(i==2)
            {
                while(p<=n)
                {
                    primes[p/8]=set_bitvalue(primes[p/8], (p%8));
                    p+=i;
                }
            }
            else
            {
                while(p<=n)
                {
                    primes[p/8]=set_bitvalue(primes[p/8], (p%8));
                    p+=(i*2);
                }
            }
        }
    }
    for(long long i=sqrt+1;i<=n;i++)
    {
        if(get_bitvalue(primes[i/8], (i%8))==0)
        {
            noofprimes++;
        }
    }
    return noofprimes;
}

long long diff_sieve(unsigned char* primes, long long n, long long sqrt, long long noofprimes)
{
    int* difference=malloc(noofprimes*sizeof(int));
    long long lastprime=2,q=0;
    for(long long i=3;i<=sqrt;i++)
    {
        if(primes[i]==0)
        {
            long long p=(i*i);
            difference[q]=(int)(i-lastprime);
            lastprime=i;
            q++;
            while(p<=n)
            {
                primes[p]=1;
                p+=(i*2);
            }
            
        }
    }
    for(long long i=sqrt+1;i<=n;i++)
    {
        if(primes[i]==0)
        {
            noofprimes++;
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
    unsigned char* diff_primes=malloc(N*sizeof(char));
    for(long i=0;i<(N/8)+1;i++)
        bit_primes[i]=0;
    for(long i=0;i<N;i++)
        diff_primes[i]=0;
    for(long i=4;i<N;i+=2)
        diff_primes[i]=1;
    square_root=sqrt(N);
    space_using_bits=N;
    clock_t t_bits=clock();
    noofprimes=bit_sieve(bit_primes,N,square_root);
    t_bits=clock()-t_bits;
    clock_t t_difference=clock();
    space_using_difference=diff_sieve(diff_primes,N,square_root,noofprimes);
    t_difference=clock()-t_difference;
    printf("\nCalculated %lld primes",noofprimes);
    printf("\nTime taken using bits method = %.2lf",(double)t_bits/CLOCKS_PER_SEC);
    printf("\nSpace taken using bits method = %lld",space_using_bits);
    printf("\nTime taken using difference method = %.2lf",(double)t_difference/CLOCKS_PER_SEC);
    printf("\nSpace taken using difference method = %lld",space_using_difference);
    free(bit_primes);
    free(diff_primes);
    return 0;
}

