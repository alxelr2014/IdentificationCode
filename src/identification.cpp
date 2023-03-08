#include "../include/identification.h"

using namespace std;

IdentificationCode::IdentificationCode(uint64_t log_number_of_messages, uint64_t block_length,uint64_t number_of_encoding_iteration)
{
    this->log_number_of_messages = log_number_of_messages;
    this->block_length = block_length;
    this->number_of_encoding_iteration = number_of_encoding_iteration;
    this->valid_construction = false;
}
IdentificationCode::~IdentificationCode()
{
}

void IdentificationCode::constructID_Code(const Channel &channel, function<void(const Channel &, IdentificationCode *)> construction_method)
{
    *getOutputStream() << "Creating the code!\n";
    construction_method(channel, this);
    this->valid_construction = true;
    *getOutputStream() << "Code Created!\n";
}
uint64_t IdentificationCode::getLogNumberOfMessages()
{
    return this->log_number_of_messages;
}
uint64_t IdentificationCode::getBlockLength()
{
    return this->block_length;
}

uint64_t IdentificationCode::getNumberOfEncodingIteration()
{
    return this->number_of_encoding_iteration;
}

void IdentificationCode::setBlockLength(uint64_t block_length)
{
    this->block_length = block_length;
}

long double IdentificationCode::getFirstKindError()
{
    if (this->valid_construction)
        return this->first_error;
    *getOutputStream() << "Not a valid construction!\n";
    return -1;
}
long double IdentificationCode::getSecondKindError()
{
    if (this->valid_construction)
        return this->second_error;
    *getOutputStream() << "Not a valid construction!\n";

    return -1;
}

void IdentificationCode::setSecondKindError(long double second_error){
    this->second_error = second_error;
}

void IdentificationCode::setEncoder( ID_EncodingFunction *enc){
    this->encoder = enc;
}
void IdentificationCode::setDecoder( ID_DecodingFunction *dec){
    this->decoder = dec;
}
void IdentificationCode::setIdentifier( ID_IdentifiyingFunction *idn){
    this->identifier = idn;
}

vector<chnl_input> *IdentificationCode::encode(BigUInt message)
{
    if (this->valid_construction)
    {
        return (*(this->encoder))(message);
    }
    *getOutputStream() << "Not a valid construction!\n";
    return nullptr;
}
long double IdentificationCode::decode(const vector<chnl_output> &received)
{
    if (this->valid_construction)
    {
        return (*(this->decoder))(received);
    }
    *getOutputStream() << "Not a valid construction!\n";
    return 0;
}

bool IdentificationCode::identify(const vector<chnl_output> &received, BigUInt message)
{
    if (this->valid_construction)
    {
        return (*(this->identifier))(received, message);
    }
    *getOutputStream() << "Not a valid construction!\n";
    return false;
}