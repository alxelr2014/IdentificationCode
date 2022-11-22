#pragma once
#include <vector>
#include <functional>
#include "channel.h"
using namespace std;

typedef function<vector<chnl_input>* (uint64_t)> TR_EncodingFunction; 
typedef function<uint64_t (const vector<chnl_output> &)> TR_DecodingFunction;
typedef pair<TR_EncodingFunction*,TR_DecodingFunction*> TR_Code;
class TransmissionCode
{
private:
    uint64_t N; // number of messages N = {1, 2, ... , N} 
    uint64_t n; // block length


    TR_EncodingFunction *encoder;
    TR_DecodingFunction *decoder;
    double error;
    bool valid_construction;

public:
    TransmissionCode(uint64_t N, uint64_t n);
    ~TransmissionCode();
    void constructTR_Code(const Channel & C, function<TR_Code* (const Channel &,uint64_t,uint64_t)> construction_method);
    uint64_t getN();
    uint64_t getn();
    double getError();
    vector<chnl_input>* encode(uint64_t message);
    uint64_t decode(const vector<chnl_output> &received);
};