#pragma once
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "../include/channel.h"
#include "../include/simulate.h"
#include "../include/codes.h"
#include "../include/rando.h"
using namespace std;

int main()
{
    Channel noiselessBSC = Channel(2, 2, new ChannelFunc([](chnl_input x)
                                                     { return x; }));
    uint64_t N = 484874;
    uint64_t n = 0;
    uint64_t m = 20;
    printf("Hello World!\n");
    simulate(m, noiselessBSC, N, n, NoiselessBSC_ID);
    printf("End\n");
    return 0;
}