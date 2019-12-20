# Big Int Calculator

## usage

1. compile

~~~bash
g++ basic.cpp -o basic
~~~

or

~~~bash
g++ mod.cpp -o mod
~~~

for exponentiating by squaring



2. start

~~~bash
./basic
~~~

or

~~~bash
./mod
~~~

for exponentiating by squaring





## Main code

I used operator overloading for a BigInt class to simplify c++ codes and logic.

~~~c++
ostream & operator << (ostream &os, BigInt a);
BigInt operator << (BigInt a, int b);
BigInt operator >> (BigInt a, int b);
bool operator > (BigInt a, BigInt b);
bool operator >= (BigInt a, BigInt b);
bool operator < (BigInt a, BigInt b);
bool operator <= (BigInt a, BigInt b);
bool operator == (BigInt a, BigInt b);
bool operator != (BigInt a, BigInt b);
BigInt operator + (BigInt a, BigInt b);
BigInt operator - (BigInt a, BigInt b);
BigInt operator * (BigInt a, BigInt b);
BigInt operator / (BigInt a, BigInt b);
bool absolute_cmp(BigInt a, BigInt b);
BigInt pushup(BigInt &a);
BigInt pushdown(BigInt &a);
~~~

Each method is organized within a operator-overloading function, and you can easily find them in my code or edit them.



## Known bugs

1. Program is inefficient in multiplication and division because of the algorithm.
2. Too much RAM space is spent during calculation, which I have no idea what to do with it.