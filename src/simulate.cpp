#include "../include/simulate.h"

void reportTransmission(uint64_t message, const vector<chnl_input> &encoded, const vector<chnl_output> &received, uint64_t decoded)
{
    *getOutputStream() << "Message: " << message << "\n"
                       << "Encoded: ";
    for (chnl_input symb : encoded)
    {
        *getOutputStream() << symb ;
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

long double reportIdentification(mpz_t message, const vector<chnl_input> &encoded, const vector<chnl_output> &received,
                            long double log_identified, uint64_t log_number_of_messages)
{

    *getOutputStream() << "Message: " << message << "\n"
                       << "Encoded: ";
    for (chnl_input symb : encoded)
    {
        *getOutputStream() << symb ;
    }
    *getOutputStream() << "\n"
                       << "Received: ";
    for (chnl_output symb : received)
    {
        *getOutputStream() << symb ;
    }
    long double log_error2 = log_identified -  log_number_of_messages;
    *getOutputStream() << "\n"
                       << "The log second kind error rate: " << log_error2 << "\n";
    return log_error2;
}

pair<uint64_t,long double> simulate(Channel &channel, uint64_t loglog_number_of_messages, uint64_t block_length, uint64_t number_of_encoding_iterations, ID_CodeGenerator* construction_method)
{
    // create the identification code
    IdentificationCode Rc = IdentificationCode(loglog_number_of_messages, block_length,number_of_encoding_iterations);
    Rc.constructID_Code(channel, construction_method);
    // uniform distribution over messages
    /*
    mpz_t message = mpz_t(LONG_LONG_MAX);
    // encode the message
    vector<chnl_input> *encoded = Rc.encode(message);

    // transmit the message over channel and put it in the {received} array
    vector<chnl_output> received;
    for (chnl_input symb : *encoded)
    {
        chnl_output rsymb = channel.transmit(symb);
        received.emplace_back(rsymb);
    }
    // decoded the recieved string
    // note that {decode} method gives the log of number of messages that could be identified from the received text.
    long double log_identified = Rc.decode(received);
    // output
    *getOutputStream() << "-----------------------\n";
    double log_error2 = reportIdentification(message, *encoded, received, log_identified, log_number_of_messages);
    *getOutputStream() << "-----------------------\n";*/
    *getOutputStream() << "The block length is " << Rc.getBlockLength() << endl;
    *getOutputStream() << "The average second kind error is " << Rc.getSecondKindError() << endl;
    *getOutputStream() << "-----------------------\n";

    // we are sending 2 prime numbers and one message. The upperbound is 3 times the number of bits of the larger prime
    return {Rc.getBlockLength(), Rc.getSecondKindError()};
}