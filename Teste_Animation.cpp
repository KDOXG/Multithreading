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

void move(control* action);
void animation(control* action);

int main(int argc, char* argv[])
{
	system("cls");
	int ch;
	control movement = control(0, 0, &ch);
	animation(&movement);
	std::thread anim(move, &movement);
	//pthread_t thread;
	//pthread_create(&thread, NULL, move, (void*)& ch);
	while ((ch = _getch()) != EOF
		&& ch != 'e');
	anim.join();
	//pthread_join(thread, NULL);
	return 0;
}

void move(control* action)
{
	//int aux;
	//pthread_t thread;
	//pthread_create(&thread, NULL, animation, (void*)& movement);
	//std::thread anim(animation, &movement);
	do
	{
		system("cls");
		//aux = *action;
		if (*action->stop == 'e') break;
		switch (*action->stop)
		{
		case 'w':
			if (action->y > 0)
				action->y--;
			break;
		case 'a':
			if (action->x > 0)
				action->x--;
			break;
		case 's':
			if (action->y < 16)
				action->y++;
			break;
		case 'd':
			if (action->x < 16)
				action->x++;
			break;
		default:
			break;
		}
		animation(action);
		m.lock();
		//pthread_mutex_lock(&m);
		*action->stop = 0;
		m.unlock();
		std::this_thread::yield();
		//pthread_mutex_unlock(&m);
		//while (*action == 0) std::this_thread::yield();
	} while (1);
	//anim.join();
	//pthread_join(thread, NULL);
	return;
}

void animation(control* action)
{
	for (unsigned k = 0; k < action->y; k++)
		printf("\n");
	for (unsigned j = 0; j < action->x; j++)
		printf(" ");
	printf("O");
	//for (unsigned short n = 0; n < USHRT_MAX; n++);
	//std::this_thread::yield();
	//sched_yield();
	return;
}
