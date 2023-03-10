#include "../include/rando.h"

string file_address;
string random_seed;
string gmp_random_seed;
gmp_randstate_t gmp_generator;


default_random_engine *getGenerator()
{
    static default_random_engine *generator = new default_random_engine;
    static bool first = true;
    if (first)
    {
        if(random_seed.empty())
        {
        printf("Please, enter a seed: ");
        getline(cin, random_seed);
        }
        seed_seq seed(random_seed.begin(), random_seed.end());
        generator->seed(seed);
    }
    first = false;
    return generator;
}


void init_gmp_generator(){
    static bool first = true;
    if(first){
    if(gmp_random_seed.empty()){
        printf("Please, enter a integer seed: ");
        getline(cin, gmp_random_seed);
    }
        mpz_t seed;
        mpz_init_set_str(seed,gmp_random_seed.c_str(),10);
        gmp_randinit_default(gmp_generator);
        gmp_randseed(gmp_generator,seed);
    }
}
fstream *getFstream()
{
    static fstream *out_stream = new fstream(file_address, ios::in | ios::out | ios::trunc);

    if(out_stream->fail() || out_stream->bad()){
        cout << out_stream->fail() << " " << out_stream->bad() << " " << endl;
        cout << "EXITING 11" << endl;
        exit(11);
    }

    return out_stream;
}

fstream *getOutputStream()
{
    return getFstream();
}
fstream *getInputStream()
{
    return getFstream();
}
