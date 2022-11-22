#include "../include/transmission.h"

TransmissionCode::TransmissionCode(uint64_t N, uint64_t n)
{
    this->N = N;
    this->n = n;
    this->valid_construction = false;
}
TransmissionCode::~TransmissionCode(){}

void TransmissionCode::constructTR_Code(const Channel &C, function<TR_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
    TR_Code *result = construction_method(C, this->N, this->n);
    this->encoder = result->first;
    this->decoder = result->second;
    this->valid_construction = true;
}

uint64_t TransmissionCode::getN()
{
    return this->N;
}
uint64_t TransmissionCode::getn()
{
    return this->n;
}

double TransmissionCode::getError()
{
    if (this->valid_construction)
        return this->error;
    return -1;
}
vector<chnl_input> *TransmissionCode::encode(uint64_t message)
{
    if (this->valid_construction)
    {
        if (message <= this->N && message > 0)
        {
            return (*(this->encoder))(message);
        }
    }
    return nullptr;
}
uint64_t TransmissionCode::decode(const vector<chnl_output> &received)
{
    if (this->valid_construction)
    {
        return (*(this->decoder))(received);
    }
    return 0;
}