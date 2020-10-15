#pragma once
#include <string>
#include "Eleint.h"
#include "BigMath.h"

using namespace std;

constexpr unsigned int UNSIGNEDINT_MAX = ~0x0;

extern unsigned int primes[];

class Bigint {
private:
	unsigned int elenum = 1;
	Eleint *topint;

	Eleint* GetElement(unsigned int n) const;
public:
	Bigint();
	Bigint(unsigned int num);
	Bigint(const Bigint& b);
	Bigint(string num);

	~Bigint();

	string toStringD() const;
	string toString() const;

	inline unsigned int GetNum(unsigned int n) const {
		return GetElement(n)->GetNum();
	}

	inline void SetNum(unsigned int n, unsigned int num) {
		GetElement(n)->SetNum(num);
	}

	inline unsigned int GetLen() const {
		return this->elenum;
	}

	void operator = (unsigned int num);
	void operator = (const Bigint& num);

	Bigint operator << (int s) const;

	void operator <<= (unsigned int s);

	Bigint operator >> (unsigned int s) const;

	void operator >>= (unsigned int s);

	Bigint operator + (unsigned int num) const;

	void operator += (unsigned int num);
	void operator += (const Bigint& b);

	Bigint operator - (unsigned int num) const;

	void operator -= (unsigned int num);
	void operator -= (const Bigint& b);

	Bigint operator * (unsigned int num) const;

	void operator *= (unsigned int num);
	void operator *= (const Bigint& num);

	unsigned int operator % (unsigned int num) const;
	Bigint operator % (const Bigint& num) const;

	void operator %= (unsigned int num);
	void operator %= (const Bigint& num);

	inline Eleint* operator [] (unsigned int n) const {
		return GetElement(n);
	}

	inline bool operator == (unsigned int num) const {
		return (this->elenum == 1 && this->GetNum(0) == num);
	}

	inline bool operator != (unsigned int num) const {
		return !((*this) == num);
	}

	inline bool operator >= (unsigned int num) const {
		return (this->elenum > 1 || this->GetNum(0) >= num);
	}
	bool operator >= (const Bigint& b) const;

	inline bool operator <= (unsigned int num) const {
		return (this->elenum == 1 && this->GetNum(0) <= num);
	}

	inline bool operator > (unsigned int num) const {
		return !((*this) <= num);
	}

	unsigned int MaxBitNum() const;

	Bigint Sqrt() const;

	bool IsPrime() const;
};