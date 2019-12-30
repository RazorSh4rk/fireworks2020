#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Rockets{
	int x;
	int y;
	int lifespan;
} Rocket;


void boom(int x, int y) {
	int radius = (rand() % 5) + 1;
	for(int i = 1; i < radius; i++){
		clear();
		mvaddstr(LINES-1, (COLS/2)-10, "2020 time my dudes");
		mvaddch(y, x, 'o');
		mvaddch(y-i, x, '|');
		mvaddch(y, x-i, '-');
		mvaddch(y+i, x, '|');
		mvaddch(y, x+i, '-');
		mvaddch(y-i, x-i, '\\');
		mvaddch(y-i, x+i, '/');
		mvaddch(y+i, x-i, '/');
		mvaddch(y+i, x+i, '\\');
		refresh();
		usleep(100000/4);
	}
}

int main(){
	initscr();
	cbreak();
	noecho();
	clear();
	curs_set(0);

	Rocket rockets[COLS];
	int index = rand() % COLS;

	for(int i = 0; i < COLS; i++){
		Rocket r;
		r.x = i;
		r.y = LINES;
		r.lifespan = rand() % (LINES - 10) + 10;
		rockets[i] = r;
	}

	while(true){
		clear();
		
		if(rockets[index].lifespan > 0){
			mvaddch(rockets[index].y, rockets[index].x, '*');
			rockets[index].lifespan--;
			rockets[index].y--;
		}else{
			boom(rockets[index].x, rockets[index].y);
			rockets[index].lifespan = rand() % (LINES - 10) + 10;
			rockets[index].y = LINES;
			index = rand() % COLS;
		}

		mvaddstr(LINES-1, (COLS/2)-10, "2020 time my dudes");
		refresh();
		usleep(100000/2);
	}

	refresh();
	getch();
	endwin();

	exit(0);
}
