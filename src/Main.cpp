#include "Main.h"

//const unsigned int MAX_NUM = 1000000000;
//const int MIN_NUM = 4949;//7à»è„ÇÃäÔêî

extern Bigint LoadProfile();
extern void SaveProfile(Bigint end);
extern void LogFactor(const Bigint& f);
extern void LogPrime(const Bigint& p);

bool isprimeflag = true;	//true: prime-judge number
bool onlineflag = false;	//true: access database
bool loadflag = false;		//true: after load
Bigint endnum;
clock_t start;

using namespace std;

Bigint n;

BOOL WINAPI ProgramClosing(DWORD ctrlType) {
	switch (ctrlType) {
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		SaveProfile(n);
		break;
	}
	return FALSE;
}

int main(void) {
	Init();
	n = LoadProfile();
	SetConsoleCtrlHandler(ProgramClosing, TRUE);
	Bigint mul(0);
	if ((n.GetNum(0) & 0x1) == 0) {
		n += 1;	//ãÙêîÇ»ÇÁéüÇÃäÔêîÇ…
	}
	bool f = false;
	if (n % 3 == (unsigned int)0) {
		n += 2;	//3ÇÃî{êîÇ»ÇÁÇŒëfêîÇ≈Ç»Ç¢Ç©ÇÁéüÇÃäÔêîÇ…
	}
	else if (n % 3 == (unsigned int)1) {
		f = true;
	}
	while (endnum >= n) {
		if (n % 5 != 0 && n % 7 != 0) {
			mul = PowExB(2, 79, n);
			mul += PowExB(3, 83, n);
			mul += PowExB(5, 89, n);
			mul += PowExB(7, 97, n);
			mul %= n;
			if (mul.GetNum(0) == 0 && mul.GetLen() == 1) {
				LogFactor(n);
				if (isprimeflag && n.IsPrime()) {
					LogPrime(n);
				}
			}
		}
		if (f) {
			n += 2;	//3ÇÃî{êîÇÕÉXÉLÉbÉv
		}
		f = !f;
		n += 2;
	}
	SaveProfile(n);
	getchar();
	return 0;
}

void LogFactor(const Bigint& f) {
	cout << "p? = " << f.toString() << endl;
	if (loadflag) {
		ofstream tempfile("temp.txt", ios::app);
		tempfile << endl << "p? = " << f.toString();
		tempfile.close();
	}
}

void LogPrime(const Bigint& p) {
	cout << "p = " << p.toString() << endl;
	if (loadflag) {
		ofstream tempfile("temp.txt", ios::app);
		tempfile << endl << "p = " << p.toString();
		tempfile.close();
	}
}

Bigint LoadProfile() {
	start = clock();
	endnum = Bigint("100000000000000000000000");
	ifstream tempfile("temp.txt", ios::in|ios::ate);
	if (!tempfile.is_open()) {
		return Bigint(11);
	}
	tempfile.seekg(-1, ios::cur);
	while (tempfile.tellg() > 0) {
		char c = tempfile.get();
		if (c == '\n') {
			break;
		}
		else {
			tempfile.seekg(-2, ios::cur);
		}
	}
	Bigint startnum;
	string buf;
	getline(tempfile, buf);
	tempfile.close();
	startnum = Bigint(buf);
	cout << "Start: " << buf << endl;
	loadflag = true;
	return startnum;
}

void SaveProfile(Bigint end) {
	if (loadflag) {
		ofstream tempfile("temp.txt", ios::app);
		tempfile << endl << "time: " << (double)(clock() - start) / 1000.0 << "s" << endl;
		tempfile << end.toString();
		tempfile.close();
	}
}

Bigint GetSection() {
	return nullptr;
}

/*
int a=0, b=0, c=0, d=0;
for (int i = 2; i < 487811; i *= 2) {
	a++;
}
for (int i = 3; i < 487811; i *= 3) {
	b++;
}
for (int i = 5; i < 487811; i *= 5) {
	c++;
}
for (int i = 7; i < 487811; i *= 7) {
	d++;
}
for (int i = 0; i <= a; i++) {
	for (int j = 0; j <= b; j++) {
		for (int k = 0; k <= c; k++) {
			for (int l = 0; l <= d; l++) {
				int m = pow(2.0, i) + pow(3.0, j) + pow(5.0, k) + pow(7.0, l);
				if (abs(m - 487811) < 10) {
					printf("%d,%d,%d,%d=%d\n",i,j,k,l,m);
				}
			}
		}
	}
}
*/