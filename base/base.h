#include <emscripten.h>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;

using i28 = __int128_t;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

i28 qpow(i28 a,i28 n,i28 p) {
	i28 x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}

bool isprime(i28 n) {
    if (n < 3)
        return n == 2;
    if (n % 2 == 0)
        return false;

    i28 s = n - 1;
    int t = 0;
    while (s % 2 == 0) {
        s >>= 1;
        t++;
    }

    for (int i = 0; i < 8; ++i) {
        i28 x = rnd()%(n-3)+2;
        i28 u = qpow(x, s, n);

        if (u == 1)
            continue;

        bool is_composite = true;
        for (int j = 0; j < t; j++) {
            if (u == n - 1) {
                is_composite = false;
                break;
            }
            u = u * u % n;
        }
        if (is_composite)
            return false;
    }

    return true;
}

i28 gcd(i28 a,i28 b) {
	return b?gcd(b,a%b):a;
}

i28 findroot(i28 n) {
    i28 m = n - 1;

    vector<i28> factor;

    for (i28 i = 2; i * i <= m; ++i) {
        if (m % i == 0) {
            factor.push_back(i);
            while (m % i == 0) {
                m /= i;
            }
        }
    }

    if (m > 1) {
        factor.push_back(m);
    }

    for (i28 i = 2; ; ++i) {
        if (gcd(i, n) == 1) {
            bool ok = true;
            for (auto j : factor) {
                if (qpow(i, (n - 1) / j, n) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return i;
            }
        }
    }
}

namespace IO {
    char *iB;
    inline char gc() {
        return *iB?*iB++:-1;
    }
    i28 read() {
        i28 x=0;
        char c=gc();
        for(; !isdigit(c); c=gc());
        for(; isdigit(c); c=gc()) x=x*10+c-'0';
        return x;
    }
    const char endl = '\n';
    struct Outputer {
        char oB[1 << 25],*oc;
        inline void pc(char c) { *oc++=c; }
        Outputer& operator<<(i28 x) {
            if(x<0) pc('-'),x=-x;
            if(x>9) *this<<x/10;
            pc('0'+x%10);
            return *this;
        }
        Outputer& operator<<(const char *s) {
            for(const char *i=s; *i; ++i) pc(*i);
            return *this;
        }
        Outputer& operator<<(const char &c) {
            pc(c);
            return *this;
        }
        char* result() { return oB; }
    } out;
    void init(char *str) {
		memset(out.oB,0,sizeof(out.oB));
        out.oc=out.oB;
		iB=str;
	}
}
