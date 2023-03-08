#include "../include/codes.h"

vector<chnl_input> *generateEncodingFunction(vector<pair<uint64_t,uint64_t>> keys, BigUInt message)
{
    uint64_t mod_result = message;
    for(uint64_t i = 0 ; i < keys.size(); i++){
        mod_result = phi(mod_result,keys[i].first);
    }
    vector<chnl_input> *res = binaryIntToVector(mod_result, keys[keys.size() - 1].second);
    return res;
}

long double generateDecodingFunction(vector<pair<uint64_t,uint64_t>> keys, uint64_t log_number_of_messages)
{
    long double log_div = log_number_of_messages -  keys[keys.size() - 1].second;
    return log_div;
}
bool generateIdentifyingFunction(vector<pair<uint64_t,uint64_t>> keys, const vector<chnl_output> &received, BigUInt message)
{

    uint64_t decimal_rem = binaryVectorToInt(received,  keys[keys.size() - 1].second);
    uint64_t cipher = message;
    for(uint64_t i = 0 ; i < keys.size(); i++){
        cipher = phi(cipher,keys[i].first);
    }
    return cipher == decimal_rem;
}

vector<pair<uint64_t,uint64_t>> millerMethod(uint64_t log_number_of_message, uint64_t number_of_encoding_iteration, double alpha)
{
    // K = [ log_2(M)^alpha ]
    vector<pair<uint64_t,uint64_t>> keys;
    uint64_t currK = log_number_of_message;
    for (uint64_t i = 0; i < number_of_encoding_iteration; i++)
    {
        currK = (uint64_t) powl(currK, alpha);
        uint64_t s = 30 * log2l(currK);
        uint64_t key = det_uniform_prime(currK, s);
        uint64_t key_bits = ceil_log(key);
        keys.push_back({key,key_bits});
        *getOutputStream() << "The parameters are K = " << currK << ", s = " << s << ", key = " << key << endl;
        currK = (uint64_t)log2l(currK);
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

void NoiselessBSC_ID(const Channel &channel, IdentificationCode *id_code)
{
    // M := number_of_messages,  n := block_length, alpha := alpha
    // pi_k := keys.first, pi_l := keys.second
    double alpha = 1.1;
    vector<pair<uint64_t,uint64_t>> keys = millerMethod(id_code->getLogNumberOfMessages(), id_code->getNumberOfEncodingIteration(), alpha);

    uint64_t block_length = keys[id_code->getNumberOfEncodingIteration() - 1].second;
    for(uint64_t i = 0 ; i < id_code->getNumberOfEncodingIteration(); i++){
        *getOutputStream() << "The " << i + 1 << "th key is " << keys[i].first << " with " << keys[i].second << " bits." << '\n';
        block_length += keys[i].second;
    }
    // create the encoder,decoder, and identifier
    ID_EncodingFunction *enc = new ID_EncodingFunction(bind(generateEncodingFunction, keys, placeholders::_1));
    ID_DecodingFunction *dec = new ID_DecodingFunction(bind(generateDecodingFunction, keys, id_code->getLogNumberOfMessages()));
    ID_IdentifiyingFunction *idn = new ID_IdentifiyingFunction(bind(generateIdentifyingFunction, keys, placeholders::_1, placeholders::_2));

    id_code->setBlockLength(block_length);
    id_code->setEncoder(enc);
    id_code->setDecoder(dec);
    id_code->setIdentifier(idn);
    id_code->setSecondKindError((long double)(1.0 / (keys[id_code->getNumberOfEncodingIteration() - 1]).first));
}