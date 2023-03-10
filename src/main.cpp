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
    uint64_t loglog_number_of_messages = (argv >= 2) ? stoull(argc[1]) : 4;
    uint64_t block_length = (argv >= 3) ? atoi(argc[2]) : 0;
    uint64_t number_of_simulation = (argv >= 4) ? atoi(argc[3]) : 30;
    uint64_t number_of_encoding_iteration = (argv >= 5) ? atoi(argc[4]) : 2;
    file_address = (argv >= 6) ? argc[5] : "D:/Backup/Codes/IdentificationChannel/logs/log-default.txt";
    random_seed = (argv >= 7) ? argc[6] : "";
    gmp_random_seed = (argv >= 8) ? argc[7]: "";
    init_gmp_generator();
    double avg_error = 0;
    uint64_t avg_block_length = 0;
    for (uint64_t i = 0; i < number_of_simulation; i++)
    {
        pair<uint64_t,double> result =  simulate(noiselessBSC, loglog_number_of_messages, block_length,number_of_encoding_iteration, NoiselessBSC_ID);
        avg_block_length += result.first;
        avg_error += result.second;
    }
    cout <<  round(avg_block_length,number_of_simulation) << " " << avg_error / number_of_simulation;
    *getOutputStream() << "LogLog of Number of Messages:" <<  loglog_number_of_messages << endl;
    *getOutputStream() << "End\n" << endl;
    getOutputStream()->flush();
    getOutputStream()->close();
    return 0;
}