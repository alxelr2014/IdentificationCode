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


ID_Code* NoiselessBSC_ID(const Channel &C, uint64_t N, uint64_t n);