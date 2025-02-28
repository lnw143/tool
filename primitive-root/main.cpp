#include "../base/base.h"

#ifdef DEBUG
char* solve(char *str)
#else
extern "C" char* EMSCRIPTEN_KEEPALIVE solve(char *str)
#endif
{
    IO::init(str);

    i28 n=IO::read();

    IO::out<<algo::findroot(n)<<IO::endl;

    return IO::out.result();
}