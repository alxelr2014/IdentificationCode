#include "../include/simulate.h"


void reportTransmission(uint64_t message, const vector<chnl_input> &encoded, const vector<chnl_output> &received, uint64_t decoded)
{
    printf("Message: %llu\n", message);
    printf("Encoded: ");
    for (chnl_input symb : encoded)
    {
        printf("%llu ", symb);
    }
    printf("\n");
    printf("Received: ");
    for (chnl_output symb : received)
    {
        printf("%llu ", symb);
    }
    printf("\n");
    printf("Decoded: %llu\n", decoded);
}

/*void simulate(uint64_t m, Channel & C, uint64_t N, uint64_t n, function<TR_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
    TransmissionCode Tc = TransmissionCode(N, n);
    Tc.constructTR_Code(C, construction_method);
    std::uniform_int_distribution<uint64_t> distribution(1, N);

    for (uint64_t i = 0; i < m; i++)
    {
        uint64_t message = distribution(*getGenerator());
        vector<chnl_input> *encoded = Tc.encode(message);
        vector<chnl_output> received;
        for (chnl_input symb : *encoded)
        {
            chnl_output rsymb = C.transmit(symb);
            if (rsymb == 0)
                return;
            received.emplace_back(rsymb);
        }
        uint64_t decoded = Tc.decode(received);
        reportTransmission(message, *encoded, received, decoded);
    }
    
}*/

double reportIdentification(uint64_t message, const vector<chnl_input> &encoded, const vector<chnl_output> &received,
                           uint64_t identified, uint64_t N)
{
    printf("Message: %llu\n", message);
    printf("Encoded: ");
    for (chnl_input symb : encoded)
    {
        printf("%llu ", symb - 1);
    }
    printf("\n");
    printf("Received: ");
    for (chnl_output symb : received)
    {
        printf("%llu ", symb - 1);
    }
    printf("\n");
    double error2 = ((double) identified)/N;
    printf("The second kind error rate: %lf\n",error2);
    return error2;
}

void simulate(uint64_t m, Channel & C, uint64_t N, uint64_t n, function<ID_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
    IdentificationCode Rc = IdentificationCode(N, n);
    Rc.constructID_Code(C, construction_method);

    std::uniform_int_distribution<uint64_t> distribution(1, N);

    double avg_error = 0;
    for (uint64_t i = 0; i < m; i++)
    {
        uint64_t message = distribution(*getGenerator());
        vector<chnl_input> *encoded = Rc.encode(message);
        vector<chnl_output> received;
        for (chnl_input symb : *encoded)
        {
            chnl_output rsymb = C.transmit(symb);
            if (rsymb == 0)
                {printf("error?!"); return;}
            received.emplace_back(rsymb);
        }
        uint64_t identified = Rc.decode(received);
        printf("-----------------------\n");
        avg_error += reportIdentification(message, *encoded, received, identified, N);
        printf("-----------------------\n");
    }
    printf("The average second kind error is %lf\n",avg_error/m);
}