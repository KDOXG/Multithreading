#include <iostream>
#include <list>
#include <random>
#include <climits>
#include <cstdlib>
#include <cstdbool>
#include <pthread.h>

/*	https://pastebin.com/84JzD3vL	*/

/*	https://docs.google.com/document/d/1qXxZWiY8NSQ7G89HWHr3YfpRt4M-mdzbEVR_OgL1LOU/	*/

/*	AVISO
*	O tipo "short int" para a lista foi escolhido apenas para rodar em tempo mais aceitável.
*	Em tipos maiores como long int ou long long int tornavam o algoritmo de teste de primalidade muito lento.
*/

struct pth_arg{
	unsigned long V;
	std::list<short> *B;
};
unsigned long v, p, c, t;
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
	p_arg->B = &buffer;	//Passagem por referência para ambas as funções poderem modificar esta lista
	for (int i = 0; i < p; i++)
	{
		while (flag)	//verifica se a pthread foi criada, caso falhe, o retorno será diferente de zero, portanto o loop persistirá
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
	{
		while(flag)
			flag = pthread_join(produtores[i],NULL);
		flag = 1;
	}
	pthread_mutex_lock(&m);
	for (int i = 0; i < c; i++)
		buffer.push_back(-1);
	pthread_mutex_unlock(&m);

	for (int i = 0; i < c; i++)
		while(flag)
			flag = pthread_join(consumidores[i],NULL);

	return 0;
}

void * produz(void* arg) //unsigned long V, std::list<short> B
{
	pth_arg *p_arg = (pth_arg*)arg;
	unsigned long V = p_arg->V;
	std::list<short> *B = p_arg->B;
	std::random_device rd;
	for (unsigned short i = 0; i < V; i++)
    	{
		while (B->size() == t)	//Limite estipulado para o buffer
			sched_yield();
		pthread_mutex_lock(&m);
		B->push_back(rand() % SHRT_MAX);
		pthread_mutex_unlock(&m);
   	 }
	pthread_exit(NULL);
}

void * consome(void* arg) //std::list<short> B
{
	pth_arg *p_arg = (pth_arg*)arg;
	std::list<short> *B = p_arg->B;
	while(1)	//Loop infinito
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
			std::cout << '[' + std::to_string(pthread_self()) + ':' + std::to_string(a) + "]\n";	//[id:numero_primo]
	}
	pthread_exit(NULL);
}

bool prime_number(short p)
{
	if (p <= 1) return false;
	if (p == 2) return true;
	p = (short)sqrt(p);
	for (short i = 3; i <= p; i+=2) if (p % i == 0) return false;
	return true;
}
