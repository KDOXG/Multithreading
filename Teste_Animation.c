#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

//std::mutex m;

struct control {
	unsigned x;
	unsigned y;
	int* stop;
};

void move(struct control* action);
void animation(struct control* action);

int main(int argc, char* argv[])
{
	system("cls");
	int ch;
	struct control movement = {
        .x = 0,
        .y = 0,
        .stop = &ch
    };
	//std::thread anim(move, &ch);
	//pthread_t thread;
	//pthread_create(&thread, NULL, move, (void*)& ch);
    animation(&movement);
	while ((ch = getch()) != EOF
		&& ch != 'e')
	{
		move(&movement);
		ch = 0;
	}
	//anim.join();
	//pthread_join(thread, NULL);
	return 0;
}

void move(struct control* action)
{
	//int aux;
	//pthread_t thread;
	//pthread_create(&thread, NULL, animation, (void*)& movement);
	//std::thread anim(animation, &movement);
	//do
	//{
		system("clear");
		//aux = *action;
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
		//m.lock();
		//pthread_mutex_lock(&m);
		//*action = 0;
		//m.unlock();
		//pthread_mutex_unlock(&m);
		//while (*action == 0) std::this_thread::yield();
	//} while (1);
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
