#include "../include/simplesim.h"

/* Generate two large prime numbers and output the block length and error rate
 Both primes are generated via the Miller-Rabin test. The parameters are given as follow
epsilon = e^{- l} , delta = 2^{- q}
K_1 = ceil((lg M)^alpha), s_1= l/2  lg(K_1), k_1 = (lg (l) + lg lg (K_1) + q)/2
Therefore, the number of bits is log (K_1) = lg alpha + lg lg M

K_2 = ceil((lg K)^alpha), s_2= l/2 ln(K_2), k_2 = (lg(l) + lg lg (K_2) + q)/2
Therefore, the number of bits is lg (K_2) = lg alpha + lg lg K_1

The block length is n = ceil(log K_1) + 2 ceil(log K_2)
The error rate
 */

void uniform_primes(mpz_ptr rop, mp_bitcnt_t n, uint32_t s, uint32_t k)
{
    for (uint32_t i = 0; i < s; i++)
    {
    mpz_urandomb(rop, gmp_generator, n);
        if (mpz_probab_prime_p(rop,k))
            return;
    }
}

pair<uint64_t, long double> simulate(uint64_t loglog_number_of_messages,uint64_t number_of_encoding_iterations, long double alpha)
{
    uint32_t l = 10, q = 10;
    uint64_t bit1 = loglog_number_of_messages + ((uint64_t)(log2l(alpha))) + 1;
    uint64_t bit2 = (uint64_t)(log2l(alpha) + log2l(bit1)) + 1;

    uint32_t s1 = l / 2 * bit1, s2 = l / 2 * bit2;
    uint32_t k1 = (3 + (uint64_t)log2l(bit1) + q) / 2,
             k2 = (3 + (uint64_t)log2l(bit2) + q) / 2;

    mpz_t prime1;
    mpz_t prime2;
         mpz_init(prime1);
         mpz_init(prime2);


    uniform_primes(prime1, bit1, s1, k1);
    uniform_primes(prime2, bit2, s2, k2);


    // is it the actual number of bit ?!
    *getOutputStream() << "The first key is " << prime1 << " with " << bit1 << " bits." << '\n';
    *getOutputStream() << "The second key is " << prime2 << " with " << bit2 << " bits." << '\n';

    uint64_t block_length = bit1 + 2 * bit2;
    return {block_length,0};
}
