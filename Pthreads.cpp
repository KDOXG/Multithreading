#include <iostream>
#include <list>
#include <climits>
#include <cstdlib>
#include <cstdbool>
#include <pthread.h>

/*	https://pastebin.com/84JzD3vL	*/

unsigned long t;
int produz(unsigned long V, std::list<long> B);
int consome(std::list<long> B);
bool prime_number(unsigned long p);

int main(int argc, char* argv[])
{
	std::list<long> buffer;
	unsigned long v, p, c;
	if (argc <= 4)	return -1;
	v = strtoul(argv[1], NULL, 0);
	p = strtoul(argv[2], NULL, 0);
	c = strtoul(argv[3], NULL, 0);
	t = strtoul(argv[4], NULL, 0);
	pthread_t produtores[p];
	pthread_t consumidores[c];

	for (int i = 0; i < p; i++)
		while (pthread_create(&produtores[i], NULL, produz, v, buffer));
	for (int i = 0; i < c; i++)
		while (pthread_create(&consumidores[i], NULL, consome, NULL));

	return 0;
}

int produz(unsigned long V, std::list<long> B)
{
	for (unsigned long i = 0; i < V; i++)
		while (B.size() == t)
			sched_yield();
		B.push_back(rand() % LONG_MAX);
	return 0;
}

int consome(std::list<long> B)
{
	while(1)
	{
		while (B.size() == 0)
			sched_yield();
		long a = B.pop_front();
		if (a < 0)
			break;
		if (prime_number(a))
		{
			//std::cout << '[' << pthread_self() << ':' << a << "]\n";
			std::cout << '[';
			syscall(__NR_gettid);
			std::cout << ':' << a << "]\n";
		}
	}
	return 0;
}

bool prime_number(long p)
{
	if (p <= 1) return false;
	for (long i = 2; i <= p / 2; i++) if (p % i == 0) return false;
	return true;
}
