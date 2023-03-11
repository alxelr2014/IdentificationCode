#include "../include/codes.h"

vector<chnl_input> *generateEncodingFunction(vector<pair<mpz_t,uint64_t>> keys, mpz_t message)
{
    mpz_t mod_result;
    mpz_init_set(mod_result, message);
    for(uint64_t i = 0 ; i < keys.size(); i++){
         phi(mod_result, mod_result, keys[i].first);
    }
    vector<chnl_input> *res ;//= binaryIntToVector(mod_result, keys[keys.size() - 1].second);
    return res;
}

long double generateDecodingFunction(vector<pair<mpz_t,uint64_t>> keys, uint64_t log_number_of_messages)
{
    long double log_div = log_number_of_messages -  keys[keys.size() - 1].second;
    return log_div;
}
bool generateIdentifyingFunction(vector<pair<mpz_t,uint64_t>> keys, const vector<chnl_output> &received, mpz_t message)
{

    // uint64_t decimal_rem = binaryVectorToInt(received,  keys[keys.size() - 1].second);
    mpz_t mod_result;
    mpz_init_set(mod_result, message);
    for(uint64_t i = 0 ; i < keys.size(); i++){
         phi(mod_result, mod_result, keys[i].first);
    }
    return true;// cipher == decimal_rem;
}

vector<pair<mpz_t,uint64_t>> millerMethod(uint64_t loglog_number_of_messages, uint64_t number_of_encoding_iteration, double alpha)
{
    // K = [ log_2(M)^alpha ]
    vector<pair<mpz_t,uint64_t>> keys(number_of_encoding_iteration);
    uint64_t curr_bit = (uint64_t) (((long double) loglog_number_of_messages )* alpha);
    for (uint64_t i = 0; i < number_of_encoding_iteration; i++)
    {
        uniform_prime(keys[i].first,curr_bit, 50);
        keys[i].second= curr_bit;
        // *getOutputStream() << "The parameters are c = " << curr_bit << ", key = " << keys[i].first << endl;
        curr_bit = (uint64_t) (log2l(curr_bit)* alpha);
    }
    return keys;
    // uint64_t K2 = ceil(log2l(K1));
    // long double C = powl(log_number_of_message,alpha);
    // the {upperbound} is given by the Prime Number Theorem (inequalities), O(K log K).
    // There are certainly {K} primes less than {upper_bound}
    // uint64_t upper_bound_K1 = ceil(C*K1*log2l(K1));
    // uint64_t upper_bound_K2 = ceil(C*K2*log2l(K2));

    // {eps_power} and {delta_power} are the set error terms
    // they are picked so that with high probability the generated number is a prime
    // const double eps_power = 30.0;
    // const double delta_power = 100.0;

    // k:= the number of repeats of Primality test, s:= the number of times a number is generated to be tested
    /*const int k1 = (log2l(log2l(upper_bound_K1)) + log2l(eps_power/2.7178) + delta_power)/2;
    const int s1 = log2l(upper_bound_K1)*eps_power;
    const int k2 = (log2l(log2l(upper_bound_K2)) + log2l(eps_power/2.7178) + delta_power)/2;
    const int s2 = log2l(upper_bound_K2)*eps_power;*/

    // uint64_t keyQ = random_prime(upper_bound_K2,s2,k2);
    // return pair<uint64_t,uint64_t>(keyK,keyQ);
}

ID_CodeGenerator* generateNoiselessBSC_ID(long double alpha){
    auto ret = new ID_CodeGenerator(bind(NoiselessBSC_ID,alpha,placeholders::_1, placeholders::_2));
    return ret;
}

void NoiselessBSC_ID(long double alpha,const Channel &channel, IdentificationCode *id_code)
{
    // M := number_of_messages,  n := block_length, alpha := alpha
    // pi_k := keys.first, pi_l := keys.second
    vector<pair<mpz_t,uint64_t>> keys = millerMethod(id_code->getLogLogNumberOfMessages(), id_code->getNumberOfEncodingIteration(), alpha);

    uint64_t block_length = keys[id_code->getNumberOfEncodingIteration() - 1].second;
    for(uint64_t i = 0 ; i < id_code->getNumberOfEncodingIteration(); i++){
        *getOutputStream() << "The " << i + 1 << "th key is " << keys[i].first << " with " << keys[i].second << " bits." << '\n';
        block_length += keys[i].second;
    }
    // create the encoder,decoder, and identifier
    ID_EncodingFunction *enc = new ID_EncodingFunction(bind(generateEncodingFunction, keys, placeholders::_1));
    ID_DecodingFunction *dec = new ID_DecodingFunction(bind(generateDecodingFunction, keys, id_code->getLogLogNumberOfMessages()));
    ID_IdentifiyingFunction *idn = new ID_IdentifiyingFunction(bind(generateIdentifyingFunction, keys, placeholders::_1, placeholders::_2));

    id_code->setBlockLength(block_length);
    id_code->setEncoder(enc);
    id_code->setDecoder(dec);
    id_code->setIdentifier(idn);
    id_code->setSecondKindError(1);
}