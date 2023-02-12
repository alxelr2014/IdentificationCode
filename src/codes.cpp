#include "../include/codes.h"

vector<chnl_input> *generateEncodingFunction(uint64_t keyK, uint64_t keyQ, uint64_t m, uint64_t n)
{
    vector<chnl_input> *res = binary_representation(phi(phi(m, keyK), keyQ), n);
    return res;
}

uint64_t generateDecodingFunction(uint64_t keyK, uint64_t keyQ, uint64_t n, uint64_t N, const vector<chnl_output> &received)
{

    uint64_t decimal_rem = decimal_representation(received, n);
    uint64_t prod = keyK * keyQ;
    uint64_t rem = N % prod;
    uint64_t div = N / prod;
    uint64_t rem_eq = 0;
    uint64_t mod_eq = 0;
    for(uint64_t i = 1; i <= prod ; i++)
    {
        uint64_t cipher = phi(phi(i,keyK), keyQ);
        if(cipher == decimal_rem){
            mod_eq++;
            (i <= rem) ? rem_eq++ : 0;
        }
    }
    return mod_eq * div + rem_eq;
}

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

pair<uint64_t, uint64_t> millerMethod(uint64_t N, double alpha){
    uint64_t K = ceil(powl(log2l(N), alpha));
    uint64_t n = 18*K*ceil(log10l(K));
    const int eps_power = 10;
    const int delta_power = 6;
    const int k = (ceil_log(n) + ceil_log(eps_power) + delta_power)/2;
    const int s = n*eps_power;
    uint64_t keyK = random_prime(n,s,k);
    uint64_t keyQ = random_prime(n,s,k);
    return pair<uint64_t,uint64_t>(keyK,keyQ); 
}


ID_Code *NoiselessBSC_ID(const Channel &C, uint64_t N, uint64_t n)
{
    double alpha = 1.1;
    //pair<uint64_t,uint64_t> keys = eratosthenesMethod(N,alpha);
    pair<uint64_t,uint64_t> keys = millerMethod(N,alpha);

    *getOutputStream() << "The keys are " << keys.first << " " << keys.second << '\n';
    n = (keys.first > keys.second) ? (ceil(log2l(keys.first))) : (ceil(log2l(keys.second)));
    ID_Code *result = new ID_Code;

    result->first = new ID_EncodingFunction(bind(generateEncodingFunction, keys.first, keys.second, placeholders::_1, n));
    result->second = new ID_DecodingFunction(bind(generateDecodingFunction, keys.first, keys.second, n,N,placeholders::_1));
    
    return result;
}