#pragma once
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include "rando.h"
using namespace std;

uint64_t simulate(uint64_t loglog_number_of_messages,  uint64_t number_of_encoding_iterations, long double alpha, mpq_ptr avg_error);