#pragma once
#include <vector>
#include <cstdint>
#include <random>
#include "rando.h"

using namespace std;
vector<uint64_t> *eratosthenesSeive(uint64_t upbound);
uint64_t phi(uint64_t m, uint64_t p);
vector<uint64_t>* binary_representation(uint64_t number, uint64_t num_digits);
uint64_t decimal_representation(const vector<uint64_t>& bin_num, uint64_t num_digits);


uint64_t exp_mod(uint64_t b, uint64_t e, uint64_t n); 
// a recursive modular exponentiation b^e mod n
bool miller_rabin(uint64_t p, uint64_t k);
// tests whether p is a prime for k iterations
uint64_t random_prime(uint64_t max, uint64_t s, uint64_t k);
// picks a number from 2 to max and returns it if it passed the miller-rabin test.
