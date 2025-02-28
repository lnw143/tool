#ifndef DEBUG
#include <emscripten.h>
#endif
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;

using i28 = __int128_t;
using u28 = __uint128_t;
using vi = vector<i28>;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

namespace algo {

u28 rnd28() { return (u28(rnd())<<64)|rnd(); }

i28 abs(i28 x) { return x<0?-x:x; }

i28 qpow(i28 a,i28 n,i28 p) {
	i28 x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}

bool isprime(i28 n) {
    if (n <= 3)
        return n >= 2;
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

i28 mul(i28 a,i28 b,i28 c) {
    i28 x=0;
    for(; b; b>>=1,a=a+a<c?a+a:a+a-c) if(b&1) x=x+a<c?x+a:x+a-c;
    return x;
}

i28 pollard_rho(i28 n) {
    const i28 c = rnd28()%(n-1)+1;
    for(i28 j=1,s=0,t=0,v=1; ; j<<=1,t=s,v=1) {
        for(i28 i=0; i<j; ++i) {
            s=mul(s,s,n)+c;
            if(s>=n) s-=n;
            v=mul(v,abs(t-s),n);
            if(!v) return n;
            if((i&127)==0) {
                i28 d=gcd(v,n);
                if(d>1) return d;
            }
        }
        i28 d=gcd(v,n);
        if(d>1) return d;
    }
    return n;
}

void get_factor(i28 x,vi &s)  {
    if(x<4||isprime(x)) {
        if(x>1) s.push_back(x);
        return ;
    }
    i28 d=x;
    while(d==x) d=pollard_rho(x);
    x/=d;
    while(x%d==0) x/=d,s.push_back(d);
    get_factor(d,s);
    get_factor(x,s);
}

i28 findroot(i28 n) {
    vector<i28> factor;

    get_factor(n-1,factor);

    sort(factor.begin(),factor.end());

    factor.erase(unique(factor.begin(),factor.end()),factor.end());

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

} // namespace algo

namespace IO {
    char *iB;
    inline char gc() {
        return *iB?*iB++:-1;
    }
    i28 read() {
        i28 x=0;
        bool f=0;
        char c=gc();
        for(; !isdigit(c); c=gc()) if(c=='-') f=1;
        for(; isdigit(c); c=gc()) x=x*10+c-'0';
        return f?-x:x;
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
