#include "../include/identification.h"

using namespace std;

IdentificationCode::IdentificationCode(uint64_t loglog_number_of_messages, uint64_t block_length,uint64_t number_of_encoding_iteration)
{
    this->loglog_number_of_messages = loglog_number_of_messages;
    this->block_length = block_length;
    this->number_of_encoding_iteration = number_of_encoding_iteration;
    this->valid_construction = false;
}
IdentificationCode::~IdentificationCode()
{
}

void IdentificationCode::constructID_Code(const Channel &channel, ID_CodeGenerator* construction_method)
{
    *getOutputStream() << "Creating the code!\n";
    (*(construction_method))(channel, this);
    this->valid_construction = true;
    *getOutputStream() << "Code Created!\n";
}
uint64_t IdentificationCode::getLogLogNumberOfMessages()
{
    return this->loglog_number_of_messages;
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

vector<chnl_input> *IdentificationCode::encode(mpz_t message)
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

bool IdentificationCode::identify(const vector<chnl_output> &received, mpz_t message)
{
    if (this->valid_construction)
    {
        return (*(this->identifier))(received, message);
    }
    *getOutputStream() << "Not a valid construction!\n";
    return false;
}