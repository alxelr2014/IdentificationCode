#include "../include/identification.h"

using namespace std;

IdentificationCode::IdentificationCode(uint64_t N, uint64_t n)
{
    this->N = N;
    this->n = n;
    this->valid_construction = false;
}
IdentificationCode::~IdentificationCode()
{
    delete this->encoder;
    delete this->decoder;
}

void IdentificationCode::constructID_Code(const Channel &C, function<ID_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
    printf("Creating the code!\n");
    ID_Code *result = construction_method(C, this->N, this->n);
    this->encoder = result->first;
    this->decoder = result->second;
    this->valid_construction = true;
    printf("Code Created!\n");
}
uint64_t IdentificationCode::getN()
{
    return this->N;
}
uint64_t IdentificationCode::getn()
{
    return this->n;
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
        if (message <= this->N && message > 0)
        {
            return (*(this->encoder))(message);
        }
        printf("Not a valid message %llu\n", message);
    }
    printf("Not a valid construction!");
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