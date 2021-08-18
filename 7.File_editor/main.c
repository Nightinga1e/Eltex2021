#include <stdio.h>
#include "stcur.h"
#include "menuwindow.h"
#include "textwindow.h"
#include "control.h"

int main()
{
	WINDOW *mwnd; //main window
	WINDOW *mswnd; //main sub
	WINDOW *twnd;	//text window
	WINDOW *tswnd; //text sub
	initscr();
	signal(SIGWINCH, sig_winch);
	refresh();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	menuwindow(&mwnd, &mswnd);
	textwindow(&twnd, &tswnd);
	control(&twnd, &tswnd);

	refresh();

	delwin(tswnd);
	delwin(twnd);
	delwin(mswnd);
	delwin(mwnd);
	endwin();
	return 0;
}
