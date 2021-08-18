#include "menuwindow.h"

int menuwindow(WINDOW **mwnd, WINDOW **mswnd)
{
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &mysize);
	*mwnd = newwin(3, mysize.ws_col, 0, 0);
	wattron(*mwnd, COLOR_PAIR(1));
	box(*mwnd, '#', '#');
	*mswnd = derwin(*mwnd, 1, mysize.ws_col-1, 1, 1);
	wbkgd(*mswnd, COLOR_PAIR(2));
	wattron(*mswnd, A_BOLD);
	wprintw(*mswnd, " F2 - open file		F3 - edit file		F4 - save file		F5 - exit \n");
	wrefresh(*mswnd);
	wrefresh(*mwnd);
	return 0;
}
