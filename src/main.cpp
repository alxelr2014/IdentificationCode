#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "../include/channel.h"
#include "../include/simulate.h"
#include "../include/codes.h"
#include "../include/rando.h"
using namespace std;

int main(int argv, char *argc[])
{
    Channel noiselessBSC = Channel(2, 2, new ChannelFunc([](chnl_input x)
                                                         { return x; }));
    file_address = (argv >= 2) ? argc[1] : "C:/Users/Emad Zinoghli/Desktop/Codes/IdentificationChannel/logs/log-default.txt";
    uint64_t N = (argv >= 3) ? atoi(argc[2]) : 10000;
    uint64_t n = (argv >= 4) ? atoi(argc[3]) : 0;
    uint64_t m = (argv >= 5) ? atoi(argc[4]) : 15;
    random_seed = (argv >= 6) ? argc[5] : "";
    double avg_error = 0;
    
    for (uint64_t i = 0; i < 10; i++)
    {
        avg_error += simulate(noiselessBSC, N, n, NoiselessBSC_ID);
    }
    cout << avg_error / m;
    *getOutputStream() << "End" << endl;
    getOutputStream()->close();
    return 0;
}