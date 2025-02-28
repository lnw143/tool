#ifdef DEBUG

#include <cstdio>

int main() {
	static char buf[1 << 22];

	char *p=buf;

	while((*p++=getchar())!=EOF);

	*p=0;

	printf("%s\n",solve(buf));

	return 0;
}

#endif