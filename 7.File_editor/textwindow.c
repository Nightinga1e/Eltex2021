#include "textwindow.h"

int textwindow(WINDOW **twnd, WINDOW **tswnd)
{
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &mysize);
	*twnd = newwin(mysize.ws_row-3, mysize.ws_col, 3, 0);
	wattron(*twnd, COLOR_PAIR(1));
	box(*twnd, '#', '#');
	*tswnd = derwin(*twnd, mysize.ws_row-5, mysize.ws_col-2, 1, 1);
	wbkgd(*tswnd, COLOR_PAIR(2));
	wattron(*tswnd, A_BOLD);
	wprintw(*tswnd, "\nOpen file to see text\n");
	wrefresh(*tswnd);
	wrefresh(*twnd);
}
