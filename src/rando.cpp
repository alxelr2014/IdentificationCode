#include "../include/rando.h"

string file_address;
string random_seed;

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
