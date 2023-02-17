#include "../include/codes.h"

vector<chnl_input> * generateEncodingFunction(uint64_t keyK, uint64_t keyQ, uint64_t message, uint64_t number_of_bits)
{
    vector<chnl_input> *res = binaryIntToVector(phi(phi(message, keyK), keyQ), number_of_bits);
    return res;
}

uint64_t generateDecodingFunction(uint64_t keyK, uint64_t keyQ, uint64_t number_of_bits, uint64_t number_of_messages, const vector<chnl_output> &received)
{
    uint64_t numer = binaryVectorToInt(received, number_of_bits);
    uint64_t prod = keyK * keyQ;
    uint64_t rem = number_of_messages % prod;
    uint64_t div = number_of_messages / prod;
    uint64_t rem_eq = 0;
    uint64_t mod_eq = 0;
    for(uint64_t i = 1; i <= prod ; i++)
    {
        uint64_t cipher = phi(phi(i,keyK), keyQ);
        if(cipher == numer){
            mod_eq++;
            (i <= rem) ? rem_eq++ : 0;
        }
    }
    return mod_eq * div + rem_eq;
}
bool generateIdentifyingFunction(uint64_t keyK, uint64_t keyQ, uint64_t number_of_bits, const vector<chnl_output> &received, uint64_t message){
    uint64_t decimal_rem = binaryVectorToInt(received, number_of_bits);
    uint64_t cipher = phi(phi(message,keyK),keyQ);
    return cipher == decimal_rem;
}
/*
pair<uint64_t, uint64_t> eratosthenesMethod(uint64_t N, double alpha){
    uint64_t K = ceil(powl(log2l(N), alpha));
    vector<uint64_t> *primes_K = eratosthenesSeive(K);
    uint64_t pK = primes_K->at(primes_K->size() - 1);
    uint64_t Q = ceil(powl(log2l(pK), alpha));
    vector<uint64_t> *primes_Q ;
    if (Q > K) primes_Q = eratosthenesSeive(Q);
    else primes_Q = primes_K;
    uint64_t pQ = primes_Q->at(primes_Q->size() - 1);

    *getOutputStream() << "K = " << K << ", Q = " << Q << ", pK = " << pK << ", pQ = " << pQ << '\n';

    uniform_int_distribution<uint64_t> distK(0, primes_K->size() - 1);
    uniform_int_distribution<uint64_t> distQ(0, primes_Q->size() - 1);

    uint64_t keyK = primes_K->at(distK(*getGenerator()));
    uint64_t keyQ = primes_Q->at(distQ(*getGenerator()));

    return pair<uint64_t,uint64_t>(keyK,keyQ);
}
*/
pair<uint64_t, uint64_t> millerMethod(uint64_t M, double alpha){
    // K = [ log_2(M)^alpha ]
    uint64_t K = ceil(powl(log2l(M), alpha));

    // the {upperbound} is given by the Prime Number Theorem (inequalities), O(K log K).
    // There are certainly {K} primes less than {upper_bound}
    uint64_t upper_bound = 18*K*ceil(log10l(K));

    // {eps_power} and {delta_power} are the set error terms
    // they are picked so that with high probability the generated number is a prime
    const int eps_power = 10;
    const int delta_power = 6;

    // k:= the number of repeats of Primality test, s:= the number of times a number is generated to be tested
    const int k = (ceil_log(upper_bound) + ceil_log(eps_power) + delta_power)/2;
    const int s = upper_bound*eps_power;

    uint64_t keyK = random_prime(upper_bound,s,k);
    uint64_t keyQ = random_prime(upper_bound,s,k);
    return pair<uint64_t,uint64_t>(keyK,keyQ); 
}


ID_Code *NoiselessBSC_ID(const Channel &channel, uint64_t number_of_message, uint64_t block_length)
{
    // M := number_of_messages,  n := block_length, alpha := alpha
    // pi_k := keys.first, pi_l := keys.second 
    double alpha = 1.1;
    //pair<uint64_t,uint64_t> keys = eratosthenesMethod(N,alpha);
    pair<uint64_t,uint64_t> keys = millerMethod(number_of_message,alpha);

    *getOutputStream() << "The keys are " << keys.first << " " << keys.second << '\n';
    uint64_t number_of_bits = (keys.first > keys.second) ? (ceil(log2l(keys.first))) : (ceil(log2l(keys.second)));

    // create the encoder,decoder, and identifier
    ID_EncodingFunction *enc = new ID_EncodingFunction(bind(generateEncodingFunction, keys.first, keys.second, placeholders::_1, number_of_bits));
    ID_DecodingFunction *dec = new ID_DecodingFunction(bind(generateDecodingFunction, keys.first, keys.second, number_of_bits,number_of_message,placeholders::_1));
    ID_IdentifiyingFunction *idn = new ID_IdentifiyingFunction(bind(generateIdentifyingFunction, keys.first, keys.second, number_of_bits,placeholders::_1,placeholders::_2));

    ID_Code* result = new ID_Code(make_tuple(enc,dec,idn));
    return result;
}