#pragma once
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <random>
#include <gmp.h>



using namespace std;

default_random_engine* getGenerator(); // a random generator
void init_gmp_generator();
fstream* getInputStream(); // an input stream
fstream* getOutputStream(); // an output stream
extern string file_address;
extern string random_seed;
extern string gmp_random_seed;
extern gmp_randstate_t gmp_generator;
