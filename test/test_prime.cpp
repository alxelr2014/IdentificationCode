#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "../include/functions.h"
#include "../include/rando.h"
using namespace std;

int main()
{
    const int n = 10;
    const int k = 7;
    const int s = 10;
    const int max = 1 << 20;
    uniform_int_distribution<uint64_t> rand_number(2, max);
    for (int i = 0; i < n; i++)
    {
        uint64_t prime = rand_number(*getGenerator());
        printf("%llu ", prime);
        bool is_prime = miller_rabin(prime, k);
        printf((is_prime) ? "is prime.\n" : "is not prime.\n");
    }
    
    printf("\n------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%llu is a prime.\n", random_prime(max, s, k));
    }
    return 0;
}