#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <random>


using namespace std;

default_random_engine* getGenerator(); // a random generator
fstream* getInputStream(); // an input stream
fstream* getOutputStream(); // an output stream
extern string file_address;
extern string random_seed;
