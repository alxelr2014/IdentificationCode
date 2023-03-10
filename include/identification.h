#pragma once
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <functional>
#include <tuple>
#include <gmp.h>
#include "channel.h"
#include "rando.h"

using namespace std;

typedef function<vector<chnl_input>* (mpz_t)> ID_EncodingFunction; // encoder
typedef function<long double (const vector<chnl_output> &)> ID_DecodingFunction; // decoder
typedef function<bool (const vector<chnl_output> &, mpz_t)> ID_IdentifiyingFunction; // identifier
// typedef tuple<ID_EncodingFunction* ,ID_DecodingFunction*,ID_IdentifiyingFunction*> ID_Code;



class IdentificationCode
{
private:
    uint64_t loglog_number_of_messages; // log of log of number of messages
    uint64_t block_length; // block length
    uint64_t number_of_encoding_iteration; // number of encoding iteration


    ID_EncodingFunction* encoder;
    ID_DecodingFunction* decoder;
    ID_IdentifiyingFunction* identifier;
    long double first_error ;
    long double second_error;
    bool valid_construction;

public:
    IdentificationCode(uint64_t loglog_number_of_messages, uint64_t block_length, uint64_t number_of_encoding_iteration);
    ~IdentificationCode();
    void constructID_Code(const Channel & channel, function<void (const Channel &,IdentificationCode *)> construction_method);
    uint64_t getLogLogNumberOfMessages();
    uint64_t getBlockLength();
    uint64_t getNumberOfEncodingIteration();
    void setBlockLength(uint64_t block_length);
    long double getFirstKindError();
    long double getSecondKindError();
    void setSecondKindError(long double second_error);
    void setEncoder( ID_EncodingFunction * enc);
    void setDecoder( ID_DecodingFunction * dec);
    void setIdentifier( ID_IdentifiyingFunction * idn);
    vector<chnl_input>* encode(mpz_t message); // encodes the message
    long double decode(const vector<chnl_output> &received); // gives the log of the number of messages the could be identified with {received}
    bool identify(const vector<chnl_output> &received, mpz_t message); // does the {received} identifies {message} 
};
