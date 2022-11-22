#include "../include/rando.h"


default_random_engine* getGenerator(){
    static default_random_engine* generator = new default_random_engine;
    static bool first = true;
    if (first)
    {
        string str;
        printf("Please, enter a seed: ");
        getline(cin, str);
        seed_seq seed(str.begin(), str.end());
        generator->seed(seed);
    }
    first = false;
    return generator;
}
