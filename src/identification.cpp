#include "../include/identification.h"

using namespace std;

IdentificationCode::IdentificationCode(uint64_t log_number_of_messages, uint64_t block_length)
{
    this->log_number_of_messages = log_number_of_messages;
    this->block_length = block_length;
    this->valid_construction = false;
}
IdentificationCode::~IdentificationCode()
{
}

void IdentificationCode::constructID_Code(const Channel &channel, function<ID_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
    *getOutputStream() << "Creating the code!\n";
    ID_Code *result = construction_method(channel, this->log_number_of_messages, this->block_length);
    this->encoder = get<0>(*result);
    this->decoder = get<1>(*result);
    this->identifier = get<2>(*result);

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
vector<chnl_input> *IdentificationCode::encode(uint64_t message)
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

bool IdentificationCode::identify(const vector<chnl_output> &received, uint64_t message)
{
    if (this->valid_construction)
    {
        return (*(this->identifier))(received, message);
    }
    *getOutputStream() << "Not a valid construction!\n";
    return false;
}