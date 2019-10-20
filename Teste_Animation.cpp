#include <iostream>
#include <cstdlib>
#include <climits>
#include <thread>
#include <mutex>
#include <conio.h>

std::mutex m;

struct control {
	unsigned x;
	unsigned y;
	int* stop;

	control(unsigned x, unsigned y, int* action)
	{
		this->x = x;
		this->y = y;
		stop = action;
	}
};

void move(int* action);
void animation(control* action);

int main(int argc, char* argv[])
{
	system("cls");
	int ch;
	std::thread anim(move, &ch);
	//pthread_t thread;
	//pthread_create(&thread, NULL, move, (void*)& ch);
	while ((ch = getch()) != EOF
		&& ch != '\n');
	anim.join();
	//pthread_join(thread, NULL);
	return 0;
}

void move(int* action)
{
	int aux;
	control movement = control(0, 0, action);
	//pthread_t thread;
	//pthread_create(&thread, NULL, animation, (void*)& movement);
	std::thread anim(animation, &movement);
	do
	{
		aux = *action;
			if (aux == '\n')
				break;
		switch (aux)
		{
		case 'w':
			if (movement.y > 0)
				movement.y--;
			break;
		case 'a':
			if (movement.x > 0)
				movement.x--;
			break;
		case 's':
			if (movement.y < 16)
				movement.y++;
			break;
		case 'd':
			if (movement.x < 16)
				movement.x++;
			break;
		default:
			break;
		}
		m.lock();
		//pthread_mutex_lock(&m);
		*action = 0;
		m.unlock();
		//pthread_mutex_unlock(&m);
		while (*action == 0) std::this_thread::yield();
	} while (1);
	anim.join();
	//pthread_join(thread, NULL);
	return;
}

void animation(control* action)
{
	unsigned long long i;
	unsigned j, k;
	for (i = 0; i < ULLONG_MAX && *(action->stop) == 0; i++)
	{
		for (k = 0; k < action->y; k++)
			printf("\n");
		for (j = 0; j < action->x; j++)
			printf(" ");
		printf("O");
		for (unsigned short n = 0; n < USHRT_MAX; n++);
		std::this_thread::yield();
		//sched_yield();
	}
	return;
}