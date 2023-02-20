#pragma once
#include <vector>
#include <deque>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

class BigUInt
{
private:
    deque<bool> number;
public:
    BigUInt(uint64_t number);
    BigUInt(const BigUInt &biguint);
    BigUInt(const vector<uint64_t> &biguint);
    BigUInt(){};
    ~BigUInt();
    BigUInt operator+(const BigUInt &a) const;
    BigUInt operator-(const BigUInt &a) const;
    BigUInt operator*(const BigUInt &a) const;
    BigUInt operator%(const BigUInt &a) const;
    uint64_t operator%(const uint64_t &a) const;
    BigUInt operator>>(uint64_t shift) const;
    BigUInt operator<<(uint64_t shift) const;
    void operator>>=(uint64_t shift);
    void operator<<=(uint64_t shift);
    bool operator<(const BigUInt &a) const;
    bool operator<=(const BigUInt &a) const;
    bool operator>(const BigUInt &a) const;
    bool operator>=(const BigUInt &a) const;
    bool operator==(const BigUInt &a) const;
    bool operator[](uint64_t index) const;
    bool isZero() const;
    uint64_t size() const;
    void setBit(uint64_t index, bool bit);
    void push_back(bool bit);
    void push_front(bool bit);
    void pop_back();
    void pop_front();
    bool back() const;
    bool front() const;
    bool empty() const;
    ostream& couting(ostream & stream) const;

    operator uint64_t() const;
    operator vector<bool>() const;
};
BigUInt unsignedAddition(const BigUInt &a, const BigUInt &b, bool subtract);
ostream& operator <<(ostream& stream, const BigUInt& a);
