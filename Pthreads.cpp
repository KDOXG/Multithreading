#include <iostream>
#include <list>
#include <climits>
#include <cstdlib>
#include <cstdbool>
#include <pthread.h>

/*	https://pastebin.com/84JzD3vL	*/

struct pth_arg{
	unsigned int V;
	std::list<long> *B;
};
unsigned long v, p, c, t, count = 0;
void * produz(void *arg);
void * consome(void *arg);
bool prime_number(long p);

int main(int argc, char* argv[])
{
	std::list<long> buffer;
	int flag = 1;
	pth_arg *p_arg;//*******
	p_arg = new pth_arg;//******
	if (argc <= 4)	return -1;

	v = strtoul(argv[1], NULL, 0);
	p = strtoul(argv[2], NULL, 0);
	c = strtoul(argv[3], NULL, 0);
	t = strtoul(argv[4], NULL, 0);
	pthread_t produtores[p];
	pthread_t consumidores[c];
	p_arg->V = v;
	p_arg->B = &buffer;
	printf("******\n");
	for (int i = 0; i < p; i++)
	{
		while (flag)
			flag = pthread_create(&produtores[i], NULL, produz, (void*)p_arg);//*****
		flag = 1;
	}
	printf("******\n");

	for (int i = 0; i < p; i++)
	{
		while (flag)
			flag = pthread_join(produtores[i],NULL);
		flag = 1;
	}

	for (int i = 0; i < c; i++)
	{
		while (flag)
			flag = pthread_create(&consumidores[i], NULL, consome, (void*)p_arg);//*****
		flag = 1;
	}
	printf("******\n");

	for (int i = 0; i < p; i++)
	{
		while (flag)
			flag = pthread_join(consumidores[i],NULL);
		flag = 1;
	}
	return 0;
}

void * produz(void* arg) //unsigned long V, std::list<long> B
{
	pth_arg *p_arg = (pth_arg*)arg;
	unsigned long V = p_arg->V;
	std::list<long> *B = p_arg->B;
	for (unsigned long i = 0; i < V; i++)
    {
		while (B->size() == t)
			sched_yield();
		B->push_back(rand() % LONG_MAX);
    }
	printf("kk\n");
    count++;
	pthread_exit(NULL);
}

void * consome(void* arg) //std::list<long> B
{
	pth_arg *p_arg = (pth_arg*)arg;
	std::list<long> *B = p_arg->B;
	while(count < p || B->size() != 0)
	{
		while (B->size() == 0)
			sched_yield();
		long a = B->front();
        B->pop_front();
		if (a == -1)
			break;
		if (prime_number(a))
			std::cout << "[" + std::to_string(pthread_self()) + ':' + std::to_string(a) + "]\n";
	}
	pthread_exit(NULL);
}

bool prime_number(long p)
{
	if (p <= 1) return false;
	printf("kk\n");
	for (long i = 2; i <= p / 2; i++) if (p % i == 0) return false;
	return true;
}
