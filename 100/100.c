#include <stdio.h>

long n1, n2;

long count_cycle(long a);
long count_max_cycle(long a, long b);

int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	while(scanf("%d %d\n", &n1, &n2) == 2) {
		printf("%d %d ", n1, n2);
		printf("%d\n", count_max_cycle(n1, n2));
	}
	return 0;
}

long count_cycle (long a) {
	int cycle = 1;
	while (a != 1) {
		if (a % 2 == 1)
			a = 3*a + 1;
		else
			a = a/2;
		cycle++;
	}
	return cycle;
}

long count_max_cycle(long a, long b) {
	long i;
	long cycle, max = 0;
	if (a < b) {
		for (i = a; i <= b; i++) {
			cycle = count_cycle(i);
			if (cycle > max)
				max = cycle;
		}
	}
	else {
		for (i = b; i <= a; i++) {
			cycle = count_cycle(i);
			if (cycle > max)
				max = cycle;
		}
	}
	return max;
}

