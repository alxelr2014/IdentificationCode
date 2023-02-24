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


void NoiselessBSC_ID(const Channel &channel,IdentificationCode * id_code); // the 3 step coding scheme