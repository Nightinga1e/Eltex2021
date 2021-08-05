#include "stcur.h"

#define MAX_LEN 15

int main()
{
	WINDOW *wnd;
	char name[MAX_LEN+1];
	
	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(TRUE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd = newwin(5, 23, 2, 2);
	wbkgd(wnd, COLOR_PAIR(1));
	wattron(wnd, A_BOLD);
	wprintw(wnd, "Enter your name...\n");
	wgetnstr(wnd, name, MAX_LEN);
	name[MAX_LEN] = 0;
	wprintw(wnd, "Hello, %s!", name);
	wrefresh(wnd);
	delwin(wnd);
	curs_set(FALSE);
	move(8, 4);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	return 0;
}
