#include "../include/biguint.h"

BigUInt::BigUInt(uint64_t number)
{
    if (number == 0)
        this->number.push_back(0);
    while (number)
    {
        this->number.push_back(number & 1);
        number >>= 1;
    }
}

BigUInt BigUIntChar(char * number)
{
    BigUInt ans;
    if (number == 0)
        ans.push_back(0);
    for(char c = *number; c;c =*++number)
    {
        if(c == '0')
            ans.push_front(0);
        else if(c == '1')
            ans.push_front(1);
    }
    return ans;
}

BigUInt::~BigUInt()
{
}
BigUInt::BigUInt(const BigUInt &biguint)
{
    this->number = biguint.number;
}
BigUInt::BigUInt(const vector<uint64_t> &biguint)
{
    this->number = deque<bool>(biguint.begin(), biguint.end());
}

BigUInt BigUInt::operator+(const BigUInt &a) const
{
    return unsignedAddition(*this, a, false);
}

BigUInt BigUInt::operator-(const BigUInt &a) const
{
    return unsignedAddition(*this, a, true);
}

BigUInt BigUInt::operator*(const BigUInt &a) const
{
    BigUInt ans(0);
    for (uint64_t i = 0; i < a.size(); i++)
    {
        if (a[i])
        {
            ans = ans + (*this << i);
        }
    }
    return ans;
}

BigUInt BigUInt::operator%(const BigUInt &a) const
{
    int64_t shift = this->size() - a.size();
    BigUInt rem(*this);
    BigUInt coef(a);
    if (shift >= 0)
    {
        coef <<= shift;
        while (shift >= 0)
        {
            if (rem > coef)
            {
                rem = rem - coef;
            }
            coef >>= 1;
            shift--;
        }
    }
    return rem;
}

uint64_t BigUInt::operator%(const uint64_t &a) const
{
    BigUInt rem = *this % BigUInt(a);

    return (uint64_t) rem;
}

BigUInt BigUInt::operator>>(uint64_t shift) const
{
    BigUInt ans(*this);
    ans >>= shift;
    return ans;
}
BigUInt BigUInt::operator<<(uint64_t shift) const
{
    BigUInt ans(*this);
    ans <<= shift;
    return ans;
}

void BigUInt::operator>>=(uint64_t shift)
{
    while (shift && !this->number.empty())
    {
        this->number.pop_front();
        shift--;
    }
    if (this->number.empty())
    {
        this->number.push_back(0);
    }
}
void BigUInt::operator<<=(uint64_t shift)
{
    while (shift)
    {
        this->number.push_front(0);
        shift--;
    }
    if (this->number.empty())
    {
        this->number.push_back(0);
    }
}

bool BigUInt::operator<(const BigUInt &a) const
{
    if (this->number.size() < a.number.size())
    {
        return true;
    }
    if (this->number.size() > a.number.size())
    {
        return false;
    }
    uint64_t index = this->number.size() - 1;
    while (index && (this->number[index] == a.number[index]))
    {
        index--;
    }
    if (index == 0 && (this->number[0] == a.number[0]))
    {
        return false;
    }
    if (this->number[index] == 1)
    {
        return false;
    }
    return true;
}
bool BigUInt::operator<=(const BigUInt &a) const
{
    if (this->number.size() < a.number.size())
    {
        return true;
    }
    if (this->number.size() > a.number.size())
    {
        return false;
    }
    uint64_t index = this->number.size() - 1;
    while (index && (this->number[index] == a.number[index]))
    {
        index--;
    }
    if (index == 0 && (this->number[0] == a.number[0]))
    {
        return true;
    }
    if (this->number[index] == 1)
    {
        return false;
    }
    return true;
}
bool BigUInt::operator==(const BigUInt &a) const
{
    if (this->number.size() != a.number.size())
    {
        return false;
    }
    uint64_t index = this->number.size() - 1;
    while (index && (this->number[index] == a.number[index]))
    {
        index--;
    }
    if (index == 0 && (this->number[0] == a.number[0]))
    {
        return true;
    }
    if (this->number[index] == 1)
    {
        return false;
    }
    return false;
}

bool BigUInt::operator>(const BigUInt &a) const
{
    return !(*this <= a);
}
bool BigUInt::operator>=(const BigUInt &a) const
{
    return !(*this < a);
}

bool BigUInt::isZero() const
{
    return (*this == BigUInt(0));
}

uint64_t BigUInt::size() const
{
    return (uint64_t)this->number.size();
}
bool BigUInt::operator[](uint64_t index) const
{
    return this->number[index];
}
void BigUInt::setBit(uint64_t index, bool bit)
{
    this->number[index] = bit;
}
void BigUInt::push_back(bool bit)
{
    this->number.push_back(bit);
}

void BigUInt::push_front(bool bit)
{
    this->number.push_front(bit);
}
void BigUInt::pop_back()
{
    this->number.pop_back();
}

void BigUInt::pop_front()
{
    this->number.pop_front();
}

bool BigUInt::empty() const
{
    return this->number.empty();
}

ostream &BigUInt::couting(ostream &stream) const
{
    if(this->size() == 0) return stream;
    for (uint64_t i = this->size() - 1; i > 0; i--)
    {
        stream << this->number[i];
    }
    stream << this->number[0];
    return stream;
}

bool BigUInt::back() const
{
    return this->number.back();
}
bool BigUInt::front() const
{
    return this->number.front();
}

BigUInt::operator uint64_t() const
{
    uint64_t ans =0;
    for(uint64_t i = this->size() -1 ; i > 0 ; i--){
        ans |= this->number[i];
        ans <<= 1;
    }
    ans |= this->number[0];
    return ans;
}
BigUInt::operator vector<bool>() const
{
    vector<bool> ans(this->number.begin(), this->number.end());
    return ans;
}

BigUInt unsignedAddition(const BigUInt &a, const BigUInt &b, bool subtract)
/*
if {subtract} = false, then calculates {a + b}.
if {subtract} = true, then it assume that {a > b} and calculates {a- b}.
*/
{
    BigUInt ans(0);
    ans.pop_back();
    uint64_t index = 0;
    bool carry = 0;
    while (index < a.size() && index < b.size())
    {
        ans.push_back(carry ^ (a[index] ^ b[index]));
        carry = ((subtract ^ a[index]) & b[index]) | (carry & ((subtract ^ a[index]) | b[index]));
        index++;
    }
    while (index < a.size())
    {
        ans.push_back(carry ^ a[index]);
        carry = carry & (subtract ^ a[index]);
        index++;
    }
    while (index < b.size())
    {
        ans.push_back(carry ^ b[index]);
        carry = carry & b[index];
        index++;
    }
    ans.push_back(carry);
    while (ans.back() == 0)
    {
        ans.pop_back();
    }
    return ans;
}

ostream &operator<<(ostream &stream, const BigUInt &a)
{
    return a.couting(stream);
}


BigUInt randomGenerator(uint64_t number_bits){
    BigUInt ans (0);
    ans.pop_back();
      std::bernoulli_distribution distribution(0.5);
      while(number_bits--){
        ans.push_back(distribution(*getGenerator()));
      }
      while(!ans.back() && !ans.empty()){
        ans.pop_back();
      }
      return ans;
}