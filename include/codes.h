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

ID_CodeGenerator* generateNoiselessBSC_ID(long double alpha);
void NoiselessBSC_ID(long double alpha,const Channel &channel,IdentificationCode * id_code); // the 3 step coding scheme