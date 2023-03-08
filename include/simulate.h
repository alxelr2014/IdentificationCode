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


pair<uint64_t, long double>  simulate(Channel & channel,uint64_t log_number_of_messages , uint64_t block_length, uint64_t number_of_encoding_iterations,
      function<void (const Channel &,IdentificationCode *)> construction_method);
/* randomly generate a messages from N= {0,2, ... , N-1} and  transmit it over the given channel with the given code*/
