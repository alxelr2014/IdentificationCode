#pragma once
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <random>
#include <cmath>
#include "channel.h"
#include "transmission.h"
#include "identification.h"
#include "functions.h"
#include "rando.h"
#include "biguint.h"


ID_Code* NoiselessBSC_ID(const Channel &channel, uint64_t log_number_of_message, uint64_t block_length); // the 3 step coding scheme