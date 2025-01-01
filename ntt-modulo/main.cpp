#include "../base/base.h"

extern "C" char* EMSCRIPTEN_KEEPALIVE solve(char *str) {
    IO::init(str);

    i28 N=IO::read(),L=IO::read(),R=IO::read();

    for (i28 i = 1; i <= N; i += 2)
        for (i28 j = i, k = 0; j <= R; j<<=1, ++k)
            if (j >= L && isprime(j + 1))
                IO::out<<i<<"*2^"<<k<<"+1="<<j+1<<",g="<<findroot(j + 1)<<IO::endl;

    return IO::out.result();
}