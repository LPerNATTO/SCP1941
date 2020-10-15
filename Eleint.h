#pragma once

class Eleint {
private:
	Eleint *nextp;
	unsigned int element;
public:
	Eleint(unsigned int num) {
		element = num;
		nextp = nullptr;
	}

	Eleint* GetNextPointer() {
		return nextp;
	}

	void SetNextPointer(Eleint* p) {
		nextp = p;
	}

	unsigned int GetNum() {
		return element;
	}

	void SetNum(unsigned int num) {
		element = num;
	}

	void operator <<= (unsigned int s) {
		element <<= s;
	}
	void operator >>= (unsigned int s) {
		element >>= s;
	}

	void operator = (Eleint* e) {
		nextp = e->nextp;
		element = e->element;
	}

	void operator += (unsigned int num) {
		if (~element > num) {
			element += num;
		}
	}
};