#include "../include/functions.h"
#include <cstdio>
vector<uint64_t> *eratosthenesSeive(uint64_t upbound)
{
    vector<bool> prime_bitset(upbound + 1, true);
    prime_bitset[0] = prime_bitset[1] = false;
    vector<uint64_t> *result = new vector<uint64_t>;
    for (uint64_t i = 2; i <= upbound; i++)
    {
        if (prime_bitset[i])
        {
            result->emplace_back(i);
            for (uint64_t j = 2 * i; j <= upbound; j += i)
                prime_bitset[j] = false;
        }
    }
    return result;
}

uint64_t phi(BigUInt m, uint64_t p)
{
    return (m % p) + 1;
}

vector<uint64_t> *binaryIntToVector(uint64_t number, uint64_t num_digits)
{
    vector<uint64_t> *result = new vector<uint64_t>;
    while (num_digits--)
    {
        result->emplace_back((number & (1)));
        number >>= 1;
    }
    return result;
}

uint64_t binaryVectorToInt(const vector<uint64_t> &bin_num, uint64_t num_digits)
{
    uint64_t result = 0;
    for (uint64_t i = 0; i < num_digits; i++)
    {   
        result |= bin_num[i] << i ;
    }
    return result;
}
uint64_t exp_mod(uint64_t b, uint64_t e, uint64_t n)
{
    if (e == 0)
        return 1;
    if (e == 1)
        return b % n;
    uint64_t e2 = e >> 1;
    uint64_t half = exp_mod(b, e2, n);
    uint64_t full = (half * half) % n;
    if (e & 1)
    {
        return (full * b) % n;
    }
    return full;
}

bool miller_rabin(uint64_t p, uint64_t k)
{
    if (p <= 1) return false;
    if (p == 2)
        return true;
    if (!(p & 1))
        return false;
    uint64_t d = p - 1;
    uint64_t s = 0;
    while (!(d & 1))
    { // while d is even
        d >>= 1;
        s++;
    }
    uniform_int_distribution<uint64_t> rand_num(2, p - 2);
    for (uint64_t i = 0; i < k; i++)
    {
        uint64_t a = rand_num(*getGenerator());
        uint64_t x = exp_mod(a, d, p);
        uint64_t y;
        for (uint64_t j = 0; j < s; j++)
        {
            y = exp_mod(x, 2, p);
            if (y == 1 && x != 1 && x != (p - 1))
                return false;
            x = y;
        }
        if (y != 1)
            return false;
    }
    return true;
}


bool isprime(uint64_t n) { //determines if n is a prime number
    const int pn = 9, p[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    for (int i = 0; i < pn; ++i)
        if (n % p[i] == 0) return (n == (uint64_t) p[i]);
    if (n < (uint64_t) p[pn - 1]) return 0;
    uint64_t s = 0, t = n - 1;
    while (~t & 1)
        t >>= 1, ++s;
    for (int i = 0; i < pn; ++i) {
        uint64_t pt = exp_mod(p[i], t, n);
        if (pt == 1) continue;
        bool ok = 0;
        for (uint64_t j = 0; j < s && !ok; ++j) {
            if (pt == n - 1) ok = 1;
            pt = exp_mod(pt, 2, n);
        }
        if (!ok) return 0;
    }
    return 1;
}


uint64_t random_prime(uint64_t max, uint64_t s, uint64_t k)
{
    // get a number between {max}/4 and {max}/2, then multiply by 2 and add 1 to get an odd number between {max}/2 and {max}
    uniform_int_distribution<uint64_t> rand_num(max >> 2, max >> 1);
    for (uint64_t i = 0; i < s; i++)
    {
        uint64_t p = 2 * rand_num(*getGenerator()) + 1;
        if (miller_rabin(p, k))
            return p;
    }
    return 23;
}

uint64_t det_uniform_prime(uint64_t max, uint64_t s){
    // get a number between {max}/4 and {max}/2, then multiply by 2 and add 1 to get an odd number between {max}/2 and {max}
    uniform_int_distribution<uint64_t> rand_num(1, max >> 1);
    for (uint64_t i = 0; i < s; i++)
    {
        uint64_t p = 2 * rand_num(*getGenerator()) + 1;
        // *getOutputStream() << "------- Number p = " << p << " is to be tested.\n";
        if (isprime(p))
            return p;
    }
    return  2 * rand_num(*getGenerator()) + 1;
}

uint64_t ceil_log(uint64_t n){
    uint64_t ans= 0;
    while(n){
        ans++;
        n/=2;
    }
    return ans;
}