#include <iostream>
#include <list>
#include <random>
#include <climits>
#include <cstdlib>
#include <cstdbool>
#include <pthread.h>

/*	https://pastebin.com/84JzD3vL	*/

struct pth_arg{
	unsigned int V;
	std::list<short> *B;
};
unsigned long v, p, c, t, count = 0;
pthread_mutex_t m;
void * produz(void *arg);
void * consome(void *arg);
bool prime_number(short p);

int main(int argc, char* argv[])
{
	std::list<short> buffer;
	int flag = 1;
	pth_arg *p_arg;
	p_arg = new pth_arg;
	if (argc <= 4)	return -1;

	v = strtoul(argv[1], NULL, 0);
	p = strtoul(argv[2], NULL, 0);
	c = strtoul(argv[3], NULL, 0);
	t = strtoul(argv[4], NULL, 0);
	pthread_t produtores[p];
	pthread_t consumidores[c];
	p_arg->V = v;
	p_arg->B = &buffer;
	for (int i = 0; i < p; i++)
	{
		while (flag)
			flag = pthread_create(&produtores[i], NULL, produz, (void*)p_arg);
		flag = 1;
	}

	for (int i = 0; i < c; i++)
	{
		while (flag)
			flag = pthread_create(&consumidores[i], NULL, consome, (void*)p_arg);
		flag = 1;
	}

	for (int i = 0; i < p; i++)
		flag = pthread_join(produtores[i],NULL);

	for (int i = 0; i < c; i++)
	{
		pthread_mutex_lock(&m);
		buffer.push_back(-1);
		pthread_mutex_unlock(&m);
	}

	for (int i = 0; i < c; i++)
		flag = pthread_join(consumidores[i],NULL);

	return 0;
}

void * produz(void* arg) //unsigned short V, std::list<short> B
{
	pth_arg *p_arg = (pth_arg*)arg;
	unsigned short V = p_arg->V;
	std::list<short> *B = p_arg->B;
	std::random_device rd;
	for (unsigned short i = 0; i < V; i++)
    {
		while (B->size() == t)
			sched_yield();
		pthread_mutex_lock(&m);
		B->push_back(rand() % SHRT_MAX);
		pthread_mutex_unlock(&m);
    }
    count++;
	pthread_exit(NULL);
}

void * consome(void* arg) //std::list<short> B
{
	pth_arg *p_arg = (pth_arg*)arg;
	std::list<short> *B = p_arg->B;
	while(count < p || B->size() != 0)
	{
		while (B->size() == 0)
			sched_yield();
		short a = B->front();
		pthread_mutex_lock(&m);
        B->pop_front();
		pthread_mutex_unlock(&m);
		if (a == -1)
			break;
		if (prime_number(abs(a)))
			std::cout << "[" + std::to_string(pthread_self()) + ':' + std::to_string(a) + "]\n";
	}
	pthread_exit(NULL);
}

bool prime_number(short p)
{
	if (p <= 1) return false;
	for (short i = 2; i < p / 2; i++) if (i % p == 0) return false;
	return true;
}
