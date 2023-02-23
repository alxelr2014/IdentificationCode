#include "../include/codes.h"

vector<chnl_input> * generateEncodingFunction(uint64_t keyK, uint64_t keyQ,uint64_t number_of_bits,BigUInt message)
{
    vector<chnl_input> *res = binaryIntToVector(phi(phi(message, keyK), keyQ),number_of_bits);
    return res;
}

long double generateDecodingFunction(uint64_t keyK, uint64_t keyQ, uint64_t number_of_bits, uint64_t log_number_of_messages, const vector<chnl_output> &received)
{
    uint64_t prod = keyQ;
    // uint64_t rem = number_of_messages % prod;
    long double log_div = log_number_of_messages -log2l(prod);
    // uint64_t rem_eq = 0;
    return log_div ;
}
bool generateIdentifyingFunction(uint64_t keyK, uint64_t keyQ, uint64_t number_of_bits, const vector<chnl_output> &received, BigUInt message){
    
    uint64_t decimal_rem = binaryVectorToInt(received,number_of_bits);
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
pair<uint64_t, uint64_t> millerMethod(uint64_t log_number_of_message, double alpha){
    // K = [ log_2(M)^alpha ]
    uint64_t K1 = log_number_of_message;
    uint64_t K2 = ceil(log2l(K1));
    long double C = powl(log_number_of_message,alpha);
    // the {upperbound} is given by the Prime Number Theorem (inequalities), O(K log K).
    // There are certainly {K} primes less than {upper_bound}
    uint64_t upper_bound_K1 = ceil(C*K1*log2l(K1));
    uint64_t upper_bound_K2 = ceil(C*K2*log2l(K2));

    // {eps_power} and {delta_power} are the set error terms
    // they are picked so that with high probability the generated number is a prime
    const double eps_power = 10.0;
    const double delta_power = 6.0;

    // k:= the number of repeats of Primality test, s:= the number of times a number is generated to be tested
    const int k1 = (log2l(log2l(upper_bound_K1)) + log2l(eps_power/2.7178) + delta_power)/2;
    const int s1 = log2l(upper_bound_K1)*eps_power;
    const int k2 = (log2l(log2l(upper_bound_K2)) + log2l(eps_power/2.7178) + delta_power)/2;
    const int s2 = log2l(upper_bound_K2)*eps_power;

    uint64_t keyK = random_prime(upper_bound_K1,s1,k1);
    uint64_t keyQ = random_prime(upper_bound_K2,s2,k2);
    return pair<uint64_t,uint64_t>(keyK,keyQ); 
}


ID_Code *NoiselessBSC_ID(const Channel &channel, uint64_t log_number_of_message, uint64_t block_length)
{
    // M := number_of_messages,  n := block_length, alpha := alpha
    // pi_k := keys.first, pi_l := keys.second 
    double alpha = 0.1;
    //pair<uint64_t,uint64_t> keys = eratosthenesMethod(N,alpha);
    pair<uint64_t,uint64_t> keys = millerMethod(log_number_of_message,alpha);

    *getOutputStream() << "The keys are " << keys.first << " " << keys.second << '\n';
    uint64_t number_of_bits = (keys.first < keys.second) ? (ceil(log2l(keys.first))) : (ceil(log2l(keys.second)));
    number_of_bits++;
    // create the encoder,decoder, and identifier
    ID_EncodingFunction *enc = new ID_EncodingFunction(bind(generateEncodingFunction, keys.first, keys.second, number_of_bits, placeholders::_1));
    ID_DecodingFunction *dec = new ID_DecodingFunction(bind(generateDecodingFunction, keys.first, keys.second, number_of_bits,log_number_of_message,placeholders::_1));
    ID_IdentifiyingFunction *idn = new ID_IdentifiyingFunction(bind(generateIdentifyingFunction, keys.first, keys.second, number_of_bits,placeholders::_1,placeholders::_2));

    ID_Code* result = new ID_Code(make_tuple(enc,dec,idn));
    return result;
}