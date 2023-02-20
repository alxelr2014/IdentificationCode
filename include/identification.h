#pragma once
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <functional>
#include <tuple>
#include "channel.h"
#include "rando.h"
#include "biguint.h"

using namespace std;

typedef function<vector<chnl_input>* (BigUInt)> ID_EncodingFunction; // encoder
typedef function<long double (const vector<chnl_output> &)> ID_DecodingFunction; // decoder
typedef function<bool (const vector<chnl_output> &, uint64_t)> ID_IdentifiyingFunction; // identifier
typedef tuple<ID_EncodingFunction* ,ID_DecodingFunction*,ID_IdentifiyingFunction*> ID_Code;



class IdentificationCode
{
private:
    uint64_t log_number_of_messages; // number of messages N = {0, 2, ... , N-1} 
    uint64_t block_length; // block length


    ID_EncodingFunction* encoder;
    ID_DecodingFunction* decoder;
    ID_IdentifiyingFunction* identifier;
    long double first_error ;
    long double second_error;
    bool valid_construction;

public:
    IdentificationCode(uint64_t log_number_of_messages, uint64_t block_length);
    ~IdentificationCode();
    void constructID_Code(const Channel & channel, function<ID_Code* (const Channel &,uint64_t,uint64_t)> construction_method);
    uint64_t getLogNumberOfMessages();
    uint64_t getBlockLength();
    long double getFirstKindError();
    long double getSecondKindError();
    vector<chnl_input>* encode(uint64_t message); // encodes the message
    long double decode(const vector<chnl_output> &received); // gives the log of the number of messages the could be identified with {received}
    bool identify(const vector<chnl_output> &received, uint64_t message); // does the {received} identifies {message} 
};
