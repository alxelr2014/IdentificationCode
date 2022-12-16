#include "../include/simulate.h"

void reportTransmission(uint64_t message, const vector<chnl_input> &encoded, const vector<chnl_output> &received, uint64_t decoded)
{
    *getOutputStream() << "Message: " << message << "\n"
                       << "Encoded: ";
    for (chnl_input symb : encoded)
    {
        *getOutputStream() << symb;
    }
    *getOutputStream() << "\n"
                       << "Received: ";
    for (chnl_output symb : received)
    {
        *getOutputStream() << symb;
    }
    *getOutputStream() << "\n"
                       << "Decoded: " << decoded << "\n";
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

    *getOutputStream() << "Message: " << message << "\n"
                       << "Encoded: ";
    for (chnl_input symb : encoded)
    {
        *getOutputStream() << symb - 1;
    }
    *getOutputStream() << "\n"
                       << "Received: ";
    for (chnl_output symb : received)
    {
        *getOutputStream() << symb - 1;
    }
    double error2 = ((double)identified) / N;
    *getOutputStream() << "\n"
                       << "The second kind error rate: " << error2 << "\n";
    return error2;
}

double simulate(Channel &C, uint64_t N, uint64_t n, function<ID_Code *(const Channel &, uint64_t, uint64_t)> construction_method)
{
        //cout << "Simulate 1" << endl;
    IdentificationCode Rc = IdentificationCode(N, n);
    Rc.constructID_Code(C, construction_method);
       // cout << "Simulate 2" << endl;
    std::uniform_int_distribution<uint64_t> distribution(1, N);

    double avg_error = 0;
    uint64_t message = distribution(*getGenerator());
    vector<chnl_input> *encoded = Rc.encode(message);
    vector<chnl_output> received;
       // cout << "Simulate 3" << endl;

    for (chnl_input symb : *encoded)
    {
        chnl_output rsymb = C.transmit(symb);
        if (rsymb == 0)
        {
            cout << "\nerror?!" << endl;
            return 0;
        }
        received.emplace_back(rsymb);
    }
       // cout << "Simulate 4" << endl;
    uint64_t identified = Rc.decode(received);
    *getOutputStream() << "-----------------------\n";
    avg_error += reportIdentification(message, *encoded, received, identified, N);
       // cout << "Simulate 5" << endl;
    *getOutputStream() << "-----------------------\n";
    *getOutputStream() << "The average second kind error is " << avg_error << endl;
      //  cout << "Simulate 6" << endl;

    return avg_error;
}