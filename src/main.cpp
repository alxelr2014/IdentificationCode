#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "../include/channel.h"
#include "../include/simulate.h"
#include "../include/codes.h"
#include "../include/rando.h"
using namespace std;


uint64_t round(uint64_t dividend, uint64_t divisor){
    uint64_t integer_part = dividend / divisor;
    uint64_t fraction_part = dividend % divisor;
    if(fraction_part < dividend >> 1){
        return integer_part;
    }
    return integer_part + 1;
}

int main(int argv, char *argc[])
{
    Channel noiselessBSC = Channel(2, 2, new ChannelFunc([](chnl_input x)
                                                         { return x; }));
    file_address = (argv >= 2) ? argc[1] : "C:/Users/Emad Zinoghli/Desktop/Codes/IdentificationChannel/logs/log-default.txt";
    uint64_t number_of_messages = (argv >= 3) ? atoi(argc[2]) : 1000000;
    uint64_t block_length = (argv >= 4) ? atoi(argc[3]) : 0;
    uint64_t number_of_simulation = (argv >= 5) ? atoi(argc[4]) : 2;
    random_seed = (argv >= 6) ? argc[5] : "";
    double avg_error = 0;
    uint64_t avg_block_length = 0;
    for (uint64_t i = 0; i < number_of_simulation; i++)
    {
        pair<uint64_t,double> result =  simulate(noiselessBSC, number_of_messages, block_length, NoiselessBSC_ID);
        avg_block_length += result.first;
        avg_error += result.second;
    }
    cout <<  round(avg_block_length,number_of_simulation) << " " << avg_error / number_of_simulation;
    *getOutputStream() << "End\n" << endl;
    getOutputStream()->flush();
    getOutputStream()->close();
    return 0;
}