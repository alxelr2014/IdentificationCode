#pragma once
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <functional>
#include "channel.h"
#include "rando.h"

using namespace std;

typedef function<vector<chnl_input>* (uint64_t)> ID_EncodingFunction; //encoder
typedef function<uint64_t (const vector<chnl_output> &)> ID_DecodingFunction; //decoder
typedef pair<ID_EncodingFunction* ,ID_DecodingFunction*> ID_Code;



class IdentificationCode
{
private:
    uint64_t N; // number of messages N = {1, 2, ... , N} 
    uint64_t n; // block length


    ID_EncodingFunction* encoder;
    ID_DecodingFunction* decoder;
    double first_error ;
    double second_error;
    bool valid_construction;

public:
    IdentificationCode(uint64_t N, uint64_t n);
    ~IdentificationCode();
    void constructID_Code(const Channel & C, function<ID_Code* (const Channel &,uint64_t,uint64_t)> construction_method);
    uint64_t getN();
    uint64_t getn();
    double getFirstKindError();
    double getSecondKindError();
    vector<chnl_input>* encode(uint64_t message);
    uint64_t decode(const vector<chnl_output> &received);
};
