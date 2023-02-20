#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../include/biguint.h"
#include "../include/rando.h"

using namespace std;

int main(){
    BigUInt a1(0);
    BigUInt a2(432542);
    BigUInt a3(23423);

    cout << a1.isZero() << endl;
    cout << a2 << endl;
    cout << a3 << endl;
    cout << (a2 + a3) << endl;
    cout << a2 - a3 << endl;
    cout << a3 - a1 << endl;
    cout << a2 % a3 << endl;
    cout << a3 << endl;
    cout << (a2 << 1) << endl;
    cout << (a2 >> 1) << endl;
    cout << a2*a3 << endl;
    return 0;
}