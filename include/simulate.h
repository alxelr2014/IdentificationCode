#pragma once
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <random>
#include "channel.h"
#include "transmission.h"
#include "identification.h"
#include "rando.h"

//void simulate(uint64_t m, Channel & C,uint64_t N , uint64_t n ,  function<TR_Code* (const Channel &,uint64_t,uint64_t)> construction_method);


double simulate(Channel & C,uint64_t N , uint64_t n ,  function<ID_Code* (const Channel &,uint64_t,uint64_t)> construction_method);
/* randomly generate a messages from N= {1,2, ... , N} and  transmit it over the given channel with the given code*/
