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

uint64_t phi(uint64_t m, uint64_t p)
{
    return (m % p) + 1;
}

vector<uint64_t>* binary_representation(uint64_t number, uint64_t num_digits){
    vector<uint64_t> *result = new vector<uint64_t>;
    while(num_digits--){
        result->emplace_back((number & (1))  + 1);
        number >>= 1;
    }
    return result;
}

uint64_t decimal_representation(const vector<uint64_t>& bin_num, uint64_t num_digits){
    uint64_t result = 0;
    for(uint64_t i = num_digits - 1 ; i > 0;i--)
        {
            result <<= 1;
            result += bin_num[i] - 1;
        }
    result <<= 1;
    result += bin_num[0] - 1;
    return result;
}