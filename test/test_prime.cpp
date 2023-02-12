#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "../include/functions.h"
#include "../include/rando.h"
using namespace std;


int main()
{
    const int eps_power = 10;
    const int delta_power = 6;
    const int n = 29;
    const int k = (ceil_log(n) + ceil_log(eps_power) + delta_power)/2;
    const int s = n*eps_power;
    const int max = (1 << n) - 1 ;
    /*uniform_int_distribution<uint64_t> rand_number(2, max);
    for (int i = 0; i < n; i++)
    {
        uint64_t prime = rand_number(*getGenerator());
        printf("%llu ", prime);
        bool is_prime = miller_rabin(prime, k);
        printf((is_prime) ? "is prime.\n" : "is not prime.\n");
    }
    
    printf("\n------\n");*/
    for (int i = 0; i < n; i++)
    {
        printf("%llu is a probable prime.\n", random_prime(max, s, k));
    }
    return 0;
}