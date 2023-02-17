#pragma once
#include <vector>
#include <cstdint>
#include <random>
#include "rando.h"

using namespace std;

uint64_t phi(uint64_t m, uint64_t p); // phi_p(m) = [m % p] + 1

vector<uint64_t>* binaryIntToVector(uint64_t number, uint64_t num_digits); // turns a binary number to a vector of bits
uint64_t binaryVectorToInt(const vector<uint64_t>& bin_num, uint64_t num_digits); // turns a vector bits to a binary number

vector<uint64_t> *eratosthenesSeive(uint64_t upbound); //implements the seive of eratosthones


uint64_t exp_mod(uint64_t b, uint64_t e, uint64_t n);  // a recursive modular exponentiation b^e mod n
bool miller_rabin(uint64_t p, uint64_t k); // tests whether p is a prime for k iterations
uint64_t random_prime(uint64_t max, uint64_t s, uint64_t k); // picks a number from 2 to max and returns it if it passed the miller-rabin test.

uint64_t ceil_log(uint64_t n); 
//calculate the number of bits of n