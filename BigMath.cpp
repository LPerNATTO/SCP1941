#pragma once
#include "BigMath.h"
#include "Bigint.h"

unsigned int primes[PRIME_NUM];

unsigned int PowMod(unsigned int base, unsigned int num, unsigned int mod) {
	Bigint t(base);
	Bigint s((unsigned int)1);
	for (int a = 0; a < 32; a++) {
		if (num & 0x1) {
			s *= t.GetNum(0);
			s %= mod;
		}
		else if (num == 0) {
			break;
		}
		t *= t.GetNum(0);
		t %= mod;
		num >>= 1;
	}
	unsigned int r = s.GetNum(0);
	return r;
}

Bigint PowModB(unsigned int base, Bigint& num, const Bigint& mod) {
	Bigint t(base);
	Bigint s((unsigned int)1);
	unsigned int m = num.MaxBitNum();
	for (unsigned int a = 0; a < m; a++) {
		if (num.GetNum(0) & 0x1) {
			s *= t;
			s %= mod;
		}
		t *= t;
		t %= mod;
		num >>= 1;
	}
	return s;
}

unsigned int PowEx(unsigned int base, unsigned int num2, unsigned int mod) {
	Bigint m((unsigned int)1);
	m <<= num2;
	m %= (mod - 1);
	unsigned int r = PowMod(base, m.GetNum(0), mod);
	return r;
}

Bigint PowExB(unsigned int base, unsigned int num2, const Bigint& mod) {
	Bigint m((unsigned int)1);
	m <<= num2;
	m %= mod - 1;
	Bigint r = PowModB(base, m, mod);
	return r;
}

unsigned int Sqrt(unsigned int num) {
	unsigned int ans = 0, m = 0, y = 0;
	int i = 0;
	for (i = 0; i < 32; i += 2) {
		if ((num >> (i + 2)) <= 0) {
			break;
		}
	}
	for (; i >= 0; i -= 2) {
		m <<= 2;
		m |= (num >> i) & 0x3;
		int c = 0;
		y = (ans << 1) + 1;
		if (y <= m) {
			m -= y;
			ans = y + 1;
		}
		else {
			ans <<= 1;
		}
	}
	return ans >> 1;
}

void Init() {
	primes[0] = 2;
	primes[1] = 3;
	unsigned int p = 5, pn = 2;
	bool f = false;
	for (unsigned int p = 5; pn < PRIME_NUM; p += 2) {
		unsigned int rt = Sqrt(p);
		bool pf = true;
		for (unsigned int b = 0; b < pn; b++) {
			if (primes[b] > rt) {
				break;
			}
			if (p % primes[b] == 0) {
				pf = false;
				break;
			}
		}
		if (pf) {
			primes[pn] = p;
			pn++;
		}
		if (f) {
			p += 2;
		}
		f = !f;
	}
}

bool Prime(unsigned int num) {
	unsigned int rt = Sqrt(num);
	for (unsigned int b = 0; b < PRIME_NUM; b++) {
		if (primes[b] > rt) {
			break;
		}
		if (num % primes[b] == 0) {
			return false;
			break;
		}
	}
	return true;
}

/*bool MillerPrime(unsigned int num, unsigned int n = MAX_CHECK) {
	unsigned int k = 0, l = num - 1, s = 0;
	for (int a = 0; a < 4 * 8; a++) {
		if (l & 0x1) {
			k = a;
			s = l;
			break;
		}
		l >>= 1;
	}
	Bigint *t = new Bigint();
	for (unsigned int a = 0; a < n; a++) {
		unsigned int r = (int)(rand()*(PRIME_NUM / (1.0 + RAND_MAX)));
		unsigned int m = PowMod(primes[r], s, num);
		(*t) = m;
		for (unsigned int b = 0; b <= k; b++) {
			if (b == k && m != 1) {
				delete t;
				return false;
			}
			(*t) *= m;
			(*t) %= num;
			m = t->GetNum(0);
			if (m == num - 1) {
				break;
			}
		}
	}
	delete t;
	return true;
}

bool MillerPrime(Bigint* b,unsigned int n = MAX_CHECK) {
	unsigned int k = 0;
	Bigint *s = new Bigint();
	Bigint *t = new Bigint(b);
	for (int a = 0; a < UNSIGNEDINT_MAX; a++) {
		if (t->GetNum(0) & 0x1) {
			k = a;
			(*s) = t;
			break;
		}
		(*t) >>= 1;
	}
	delete t;
	for (unsigned int a = 0; a < n; a++) {
		unsigned int r = (int)(rand()*(PRIME_NUM / (1.0 + RAND_MAX)));
		Bigint *m = PowMod(primes[r], s, b);
		for (unsigned int b = 0; b <= k; b++) {
			if (b == k && m->GetNum(0) != 1 && m->elenum == 1) {
				delete m;
				delete t;
				return false;
			}
			m->Pow(2);
			(*m) %= b;
			t = new Bigint(b);
			t -= m;
			if (t->elenum == 1 && t->GetNum(0) == 1) {
				break;
			}
		}
		delete m;
	}
	delete t;
	return true;
}*/