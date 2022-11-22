#pragma once
#include <vector>
#include <cstdint>

using namespace std;
vector<uint64_t> *eratosthenesSeive(uint64_t upbound);
uint64_t phi(uint64_t m, uint64_t p);
vector<uint64_t>* binary_representation(uint64_t number, uint64_t num_digits);
uint64_t decimal_representation(const vector<uint64_t>& bin_num, uint64_t num_digits);
