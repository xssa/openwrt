#include <time.h>
#include <stdio.h>

int main()
{
	struct timespec t0, t;
	unsigned i, x=0;
	clock_gettime(CLOCK_REALTIME, &t0);
	for (i=0; i<1000000; i++) {
		register void *tp __asm__("$3");
#ifdef DO_RDHWR
		__asm__ __volatile__(".word 0x7c03e83b" : "=r"(tp));
#else
		__asm__ __volatile__("move %0,$0" : "=r"(tp));
#endif
		x += (unsigned)tp;
	}
	clock_gettime(CLOCK_REALTIME, &t);
	t.tv_sec -= t0.tv_sec;
	if ((t.tv_nsec -= t0.tv_nsec) < 0) {
		t.tv_nsec += 1000000000;
		t.tv_sec--;
	}
	printf("%u %lld.%.9ld\n", x, (long long)t.tv_sec, t.tv_nsec);
}


