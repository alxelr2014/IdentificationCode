#include "../include/identification.h"

using namespace std;

IdentificationCode::IdentificationCode(uint64_t number_of_messages, uint64_t block_length)
{
    this->number_of_messages = number_of_messages;
    this->block_length = block_length;
    this->valid_construction = false;
}
IdentificationCode::~IdentificationCode()
{

}

void IdentificationCode::constructID_Code(const Channel &channel, function<ID_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
    *getOutputStream() << "Creating the code!\n";
    ID_Code *result = construction_method(channel, this->number_of_messages, this->block_length);
    this->encoder = get<0>(*result);
    this->decoder = get<1>(*result);
    this->identifier = get<2>(*result);

    this->valid_construction = true;
    *getOutputStream() << "Code Created!\n";
}
uint64_t IdentificationCode::getNumberOfMessages()
{
    return this->number_of_messages;
}
uint64_t IdentificationCode::getBlockLength()
{
    return this->block_length;
}

double IdentificationCode::getFirstKindError()
{
    if (this->valid_construction)
        return this->first_error;
    return -1;
}
double IdentificationCode::getSecondKindError()
{
    if (this->valid_construction)
        return this->second_error;
    return -1;
}
vector<chnl_input> *IdentificationCode::encode(uint64_t message)
{
    if (this->valid_construction)
    {
        if (message <= this->number_of_messages && message > 0)
        {
            return (*(this->encoder))(message);
        }
        *getOutputStream() << "Not a valid message " << message << '\n';
    }
    *getOutputStream() << "Not a valid construction!\n" ;
    return nullptr;
}
uint64_t IdentificationCode::decode(const vector<chnl_output> &received)
{
    if (this->valid_construction)
    {
        return (*(this->decoder))(received);
    }
    return 0;
}

bool IdentificationCode::identify(const vector<chnl_output> &received, uint64_t message){
    if(this->valid_construction){
        return (*(this->identifier))(received,message);
    }
    return false;
}