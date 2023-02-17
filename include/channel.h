#pragma once
#include <cstdlib>
#include <cstdint>
#include <functional>
#include <vector>

using namespace std;

typedef function<uint64_t(uint64_t)> ChannelFunc;
typedef uint64_t chnl_output;
typedef uint64_t chnl_input;
class Channel
{
private:
    uint64_t x, y; /* size of the input and output alphabet
     X = {0, 2, ... , x-1} , Y = {0, 2, ... , y-1} */
    ChannelFunc* f; // the randomized function of channel

public:
    Channel(uint64_t x, uint64_t y, ChannelFunc* f);
    ~Channel();
    chnl_output transmit(chnl_input symb); // returns the result of tranmission of symb
};
