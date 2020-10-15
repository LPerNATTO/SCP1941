#pragma once
class Bigint;

constexpr unsigned int MAX_CHECK = 10;
constexpr unsigned int PRIME_NUM = 78498;

extern unsigned int primes[PRIME_NUM];

unsigned int PowMod(unsigned int base, unsigned int num, unsigned int mod);
Bigint PowModB(unsigned int base, Bigint& num, const Bigint& mod);

unsigned int PowEx(unsigned int base, unsigned int num2, unsigned int mod);
Bigint PowExB(unsigned int base, unsigned int num2, const Bigint& mod);

unsigned int Sqrt(unsigned int num);

void Init();
bool Prime(unsigned int num);