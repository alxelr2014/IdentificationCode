#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>
#include "../include/channel.h"
#include "../include/simulate.h"
#include "../include/codes.h"
#include "../include/rando.h"
#include "../include/simplesim.h"

using namespace std;
using namespace std::chrono;

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
    uint64_t loglog_number_of_messages = (argv >= 2) ? stoull(argc[1]) : 4;
    uint64_t block_length = (argv >= 3) ? atoi(argc[2]) : 0;
    uint64_t number_of_simulation = (argv >= 4) ? atoi(argc[3]) : 30;
    uint64_t number_of_encoding_iteration = (argv >= 5) ? atoi(argc[4]) : 2;
    long double alpha = (argv >= 6) ? stold(argc[5]) : 1.1; 
    file_address = (argv >= 7) ? argc[6] : "D:/Backup/Codes/IdentificationChannel/logs/log-default.txt";
    random_seed = (argv >= 8) ? argc[7] : "";
    gmp_random_seed = (argv >= 9) ? argc[8]: "";

    init_gmp_generator();
    long double avg_error = 0;
    uint64_t avg_block_length = 0;
    high_resolution_clock::time_point start,end;
    uint64_t avg_time;

    for (uint64_t i = 0; i < number_of_simulation; i++)
    {
        start = high_resolution_clock::now();
        pair<uint64_t,long double> result =  simulate(loglog_number_of_messages,number_of_encoding_iteration,alpha);
        end = high_resolution_clock::now();

        avg_time += duration_cast<std::chrono::microseconds>(end-start).count();
        avg_block_length += result.first;
        avg_error += result.second;
    }

    cout <<  round(avg_block_length,number_of_simulation) << " " << avg_error / number_of_simulation << " " << avg_time / number_of_simulation;
    *getOutputStream() << "LogLog of Number of Messages:" <<  loglog_number_of_messages << endl;
    *getOutputStream() << "End\n" << endl;
    getOutputStream()->flush();
    getOutputStream()->close();
    return 0;
}

/*
    Channel noiselessBSC = Channel(2, 2, new ChannelFunc([](chnl_input x)
                                                         { return x; }));
    init_gmp_generator();
    double avg_error = 0;
    uint64_t avg_block_length = 0;
    high_resolution_clock::time_point start,end;
    uint64_t avg_time;
    ID_CodeGenerator* NoiselessCode = generateNoiselessBSC_ID(alpha);

    for (uint64_t i = 0; i < number_of_simulation; i++)
    {
        start = high_resolution_clock::now();
        pair<uint64_t,double> result =  simulate(noiselessBSC, loglog_number_of_messages, block_length,number_of_encoding_iteration, NoiselessCode);
        end = high_resolution_clock::now();
        avg_time += duration_cast<std::chrono::microseconds>(end-start).count();

        avg_block_length += result.first;
        avg_error += result.second;
    }
*/