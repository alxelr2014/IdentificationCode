#include "../include/channel.h"

Channel::Channel(uint64_t x, uint64_t y, ChannelFunc* f)
{
    this->x = x;
    this->y = y;
    this->f = f;
}
Channel::~Channel(){
}
chnl_output Channel::transmit(chnl_input symb){
    if(symb <= this->x && symb > 0)
        return (*(this->f))(symb);
    return 0;
}
