#include "Bigint.h"

using namespace std;

Eleint* Bigint::GetElement(unsigned int n) const {
	Eleint *t = this->topint;
	for (unsigned int a = 0; a < n; a++) {
		t = t->GetNextPointer();
	}
	return t;
}

Bigint::Bigint() {
	topint = new Eleint(0);
}

Bigint::Bigint(unsigned int num) {
	topint = new Eleint(num);
}

Bigint::Bigint(const Bigint& b) {
	topint = new Eleint(b.topint->GetNum());
	Eleint *t = topint;
	for (unsigned int a = 1; a < b.elenum; a++) {
		t->SetNextPointer(new Eleint(b[a]->GetNum()));
		t = t->GetNextPointer();
		elenum++;
	}
}

Bigint::Bigint(string num) {
	Bigint bcd(0);
	for (unsigned int i = 0; i < num.length(); i++) {
		if (num[i] < '0' && num[i] > '9') {
			break;
		}
		bcd <<= 4;
		bcd += (num[i] - '0');
	}
	topint = new Eleint(0);
	Eleint *p = topint;
	int i = 0;
	unsigned int t = 0;
	unsigned int u = 0;
	unsigned int v = 0;
	unsigned int w = 0;
	while (bcd > 0) {
		if (i & 0x20) {
			i = 0;
			p->SetNum(t);
			t = 0;
			p->SetNextPointer(new Eleint(0));
			elenum++;
			p = p->GetNextPointer();
		}
		if (bcd.GetNum(0) & 0x1) {
			t |= 1 << i;
		}
		bcd >>= 1;
		for (unsigned int j = 0; j < bcd.elenum; j++) {
			u = bcd.GetNum(j);
			v = 0;
			for (int k = 0; k < 8; k++) {
				w = u & 0xF;
				v |= (w >= 8 ? w - 3 : w) << (k << 2);
				u >>= 4;
			}
			bcd.SetNum(j, v);
		}
		i++;
	}
	p->SetNum(t);
}

Bigint::~Bigint() {
	Eleint *t;
	Eleint *nt = topint;
	for (unsigned int a = 0; a < elenum; a++) {
		t = nt;
		if (a < elenum - 1) {
			nt = nt->GetNextPointer();
		}
		delete t;
	}
}

string Bigint::toStringD() const {
	string r = "";
	for (unsigned int i = 0; i < this->elenum - 1; i++) {
		string s = "";
		int t = this->GetNum(i);
		for (int j = 0; j < 32; j++) {
			s = (char)((t & 0x1) + '0') + s;
			t >>= 1;
		}
		r = s + r;
	}
	int t = this->GetNum(this->elenum - 1);
	for (int j = 0; j < 32; j++) {
		r = (char)((t & 0x1) + '0') + r;
		t >>= 1;
	}
	return r;
}

string Bigint::toString() const {
	Bigint t(0);
	for (int i = this->elenum - 1; i >= 0; i--) {
		for (int j = (i < (int)this->elenum - 1 ? 32 : this->MaxBitNum() & 0x1F); j > 0; j--) {
			for (int k = t.elenum - 1; k >= 0; k--) {
				unsigned int u = t.GetNum(k);
				unsigned int v = 0;
				for (int l = 0; l < 8; l++) {
					unsigned int w = u & 0xF;
					if (w >= 5) {
						w += 3;
					}
					v |= w << (l << 2);
					u >>= 4;
				}
				t.SetNum(k, v);
			}
			t <<= 1;
			if (this->GetNum(i) >> (j - 1) & 0x1) {
				t += 1;
			}
		}
	}
	string result = "";
	for (int i = t.elenum - 1; i >= 0; i--) {
		unsigned int u = t.GetNum(i);
		for (int j = (i < (int)t.elenum - 1 ? 8 - 1 : ((t.MaxBitNum() - 1) & 0x1F) >> 2); j >= 0; j--) {
			unsigned int v = (u >> (j << 2)) & 0xF;
			result += ('0' + v);
		}
	}
	return result;
}

void Bigint::operator = (unsigned int num) {
	if (this->elenum > 1) {
		Eleint *t;
		Eleint *nt = topint->GetNextPointer();
		for (unsigned int a = 1; a < this->elenum; a++) {
			t = nt;
			if (a < this->elenum - 1) {
				nt = nt->GetNextPointer();
			}
			delete t;
		}
	}
	this->topint->SetNum(num);
	this->topint->SetNextPointer(0);
	this->elenum = 1;
}
void Bigint::operator = (const Bigint& num) {
	for (unsigned int i = this->elenum - 1; i > num.elenum; i--) {
		delete this->GetElement(i);
		this->elenum--;
	}
	for (int i = 0; i < (int)num.elenum; i++) {
		if (i >= (int)this->elenum) {
			this->GetElement(i - 1)->SetNextPointer(new Eleint(num.GetNum(i)));
			this->elenum++;
		}
		else {
			this->GetElement(i)->SetNum(num.GetNum(i));
		}
	}
}

Bigint Bigint::operator << (int s) const {
	Bigint t(*this);
	t <<= s;
	return t;
}

void Bigint::operator <<= (unsigned int s) {
	for (int b = s / 32; b >= 0; b--) {
		if (b > 0) {
			s -= 32;
			Eleint* e = new Eleint(0);
			e->SetNextPointer(this->topint);
			this->topint = e;
			this->elenum++;
		}
		else {
			if (s > 0) {
				for (unsigned int a = this->elenum; a > 0; a--) {
					unsigned int bt = GetNum(a - 1);
					unsigned int t = bt >> (4 * 8 - s);
					(*(*this)[a - 1]) <<= s;
					if (t > 0) {
						if (a == this->elenum) {
							Eleint* e = new Eleint(t);
							(*this)[a - 1]->SetNextPointer(e);
							this->elenum++;
						}
						else {
							(*(*this)[a]) += t;
						}
					}
				}
			}
		}
	}
}

Bigint Bigint::operator >> (unsigned int s) const {
	Bigint t(*this);
	t >>= s;
	return t;
}

void Bigint::operator >>= (unsigned int s) {
	for (unsigned int a = 0; a < this->elenum; a++) {
		unsigned int bt = GetNum(a);
		unsigned int t = bt & (UNSIGNEDINT_MAX >> (4 * 8 - s));
		(*(*this)[a]) >>= s;
		if (a > 0) {
			(*(*this)[a - 1]) += (t << (4 * 8 - s));
			if (a == this->elenum - 1 && (*this)[a]->GetNum() == 0) {
				delete (*this)[a];
				(*this)[a - 1]->SetNextPointer(0);
				elenum--;
			}
		}
	}
}

Bigint Bigint::operator + (unsigned int num) const {
	Bigint t(*this);
	t += num;
	return t;
}

void Bigint::operator += (unsigned int num) {
	if (this->GetNum(0) >= ~num + 1 && this->GetNum(0) > 0 && num > 0) {
		for (unsigned int a = 0; a <= this->elenum; a++) {
			if (a == this->elenum) {
				Eleint *t = new Eleint(1);
				this->GetElement(this->elenum - 1)->SetNextPointer(t);
				this->elenum++;
				break;
			}
			else if (a != 0) {
				this->SetNum(a, this->GetNum(a) + 1);
				if (this->GetNum(a)) {
					break;
				}
			}
		}
	}
	this->SetNum(0, this->GetNum(0) + num);
}
void Bigint::operator += (const Bigint& b) {
	for (unsigned int a = 0; a < b.elenum; a++) {
		if (this->elenum > a) {
			if (this->GetNum(a) >= ~b.GetNum(a) + 1 && this->GetNum(a) > 0 && b.GetNum(a) > 0) {
				for (unsigned int c = a; c <= this->elenum; c++) {
					if (c == this->elenum) {
						Eleint *t = new Eleint(1);
						this->GetElement(this->elenum - 1)->SetNextPointer(t);
						this->elenum++;
						break;
					}
					else if (c != a) {
						this->SetNum(c, this->GetNum(c) + 1);
						if (this->GetNum(c)) {
							break;
						}
					}
				}
			}
			this->SetNum(a, this->GetNum(a) + b.GetNum(a));
		}
		else {
			Eleint *t = new Eleint(b.GetNum(a));
			this->GetElement(this->elenum - 1)->SetNextPointer(t);
			this->elenum++;
			break;
		}
	}
}

Bigint Bigint::operator - (unsigned int num) const {
	Bigint t(*this);
	t -= num;
	return t;
}

void Bigint::operator -= (unsigned int num) {
	if (this->GetNum(0) >= num) {
		this->SetNum(0, this->GetNum(0) - num);
	}
	else {
		for (unsigned int a = 1; a < this->elenum; a++) {
			if (this->GetNum(a) > 0) {
				this->SetNum(a, this->GetNum(a) - 1);
				if (this->GetNum(a) == 0) {
					delete this->GetElement(a);
					this->GetElement(a - 1)->SetNextPointer(0);
					this->elenum--;
				}
				break;
			}
			else {
				this->SetNum(a, UNSIGNEDINT_MAX);
			}
		}
		this->SetNum(0, this->GetNum(0) + (~num) + 1);
	}
}
void Bigint::operator -= (const Bigint& b) {
	if (b.elenum > this->elenum) {
		(*this) = (unsigned int)0;
	}
	else {
		for (int a = b.elenum - 1; a >= 0; a--) {
			if (this->GetNum(a) >= b.GetNum(a)) {
				this->SetNum(a, this->GetNum(a) - b.GetNum(a));
			}
			else {
				if (a == this->elenum - 1) {
					(*this) = (unsigned int)0;
					break;
				}
				else {
					this->SetNum(a, this->GetNum(a) + (~b.GetNum(a)) + 1);
				}
				for (unsigned int c = a + 1; c < this->elenum; c++) {
					if (c == this->elenum) {
					}
					if (this->GetNum(c) > 0) {
						this->SetNum(c, this->GetNum(c) - 1);
						if (this->GetNum(c) == 0) {
							delete this->GetElement(c);
							this->GetElement(c - 1)->SetNextPointer(0);
							this->elenum--;
						}
						break;
					}
					else {
						if (c == this->elenum - 1) {
							(*this) = (unsigned int)0;
						}
						else {
							this->SetNum(c, UNSIGNEDINT_MAX);
						}
					}
				}
			}
		}
		for (int i = this->elenum - 1; i > 0; i--) {
			if (this->GetNum(i) == 0) {
				this->elenum--;
				delete this->GetElement(i);
				this->GetElement(i - 1)->SetNextPointer(NULL);
			}
			else {
				break;
			}
		}
	}
}

Bigint Bigint::operator * (unsigned int num) const {
	Bigint t(*this);
	t *= num;
	return t;
}

void Bigint::operator *= (unsigned int num) {
	if (num == 0) {
		(*this) = (unsigned int)0;
	}
	else {
		num--;
		Bigint t(*this);
		for (int a = 0; a < 4 * 8; a++) {
			if (num % 2) {
				(*this) += t;
			}
			t <<= 1;
			num >>= 1;
			if (!num) {
				break;
			}
		}
	}
}
void Bigint::operator *= (const Bigint& num) {
	Bigint t(num);
	Bigint r(0);
	while (t != 0) {
		if (t.GetNum(0) & 0x1) {
			r += (*this);
		}
		(*this) <<= 1;
		t >>= 1;
	}
	(*this) = r;
}

unsigned int Bigint::operator % (unsigned int num) const {
	Bigint t(*this);
	t %= num;
	unsigned int r = t.GetNum(0);
	return r;
}
Bigint Bigint::operator % (const Bigint& num) const {
	Bigint t(*this);
	t %= num;
	return t;
}

void Bigint::operator %= (unsigned int num) {
	Bigint s(0);
	unsigned int k = (UNSIGNEDINT_MAX % num) + 1;
	unsigned long t;
	s = this->GetNum(0) % num;
	for (unsigned int a = 1; a < this->elenum; a++) {
		s += k * (this->GetNum(a) % num);
		s %= num;
		t = k * k;
		k = t % num;
	}
	(*this) = s;
}
void Bigint::operator %= (const Bigint& num) {
	Bigint s(num);
	int m = this->MaxBitNum() - num.MaxBitNum();
	if (m > 0) {
		s <<= m;
		for (int i = 0; i <= m; i++) {
			if ((*this) >= s) {
				(*this) -= s;
				if (this->MaxBitNum() < num.MaxBitNum()) {
					break;
				}
			}
			s >>= 1;
		}
	}
}

bool Bigint::operator >= (const Bigint& b) const {
	if (this->elenum > b.elenum) {
		return true;
	}
	else if (this->elenum < b.elenum) {
		return false;
	}
	else {
		for (unsigned int a = this->elenum - 1; a >= 0; a--) {
			if (this->GetNum(a) > b.GetNum(a)) {
				return true;
			}
			else if (this->GetNum(a) < b.GetNum(a)) {
				return false;
			}
			if (a == 0) {
				return true;
			}
		}
		return true;
	}
}

unsigned int Bigint::MaxBitNum() const {
	unsigned int r = (elenum - 1) << 5;
	unsigned int t = this->GetNum(elenum - 1);
	for (int i = 0; i < 32; i++) {
		if (t) {
			r++;
			t >>= 1;
		}
		else {
			break;
		}
	}
	return r;
}

Bigint Bigint::Sqrt() const {
	Bigint ans(0);
	Bigint r(0);
	unsigned int y = 0;
	int i = 0;
	for (int i = (this->MaxBitNum() - 1) & 0xFFFE; i >= 0; i -= 2) {
		r <<= 2;
		r += (this->GetNum(i >> 5) >> (i & 0x1F)) & 0x3;
		Bigint t = ans << 1;
		t += 1;
		if (r >= t) {
			r -= t;
			ans += 1;
			ans <<= 1;
		}
		else {
			ans <<= 1;
		}
	}
	ans >>= 1;
	return ans;
}

bool Bigint::IsPrime() const {
	for (unsigned int i = 4; i < PRIME_NUM; i++) {
		if ((*this) <= primes[i]) {
			return true;
		}
		if ((*this) % primes[i] == 0) {
			return false;
		}
	}
	Bigint i(primes[PRIME_NUM - 1] + 2);
	Bigint sq = this->Sqrt();
	for (; sq >= i; i += 2) {
		Bigint r = (*this) % i;
		if (r == 0) {
			return false;
		}
	}
	return true;
}