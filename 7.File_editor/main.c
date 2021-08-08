#include "stcur.h"

struct winsize mysize;

int menuwindow(WINDOW **win, WINDOW **sub)
{
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &mysize);
	*win = newwin(3, mysize.ws_col, 0, 0);
	wattron(*win, COLOR_PAIR(1));
	box(*win, '#', '#');
	*sub = derwin(*win, 1, mysize.ws_col-1, 1, 1);
	wbkgd(*sub, COLOR_PAIR(2));
	wattron(*sub, A_BOLD);
	wprintw(*sub, " F1 - open file		F2 - save file		F3 - exit \n");
	wrefresh(*sub);
	wrefresh(*win);
	return 0;
}

int textwindow(WINDOW **text, WINDOW **subtext)
{
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &mysize);
	*text = newwin(mysize.ws_row-3, mysize.ws_col, 3, 0);
	wattron(*text, COLOR_PAIR(1));
	box(*text, '#', '#');
	*subtext = derwin(*text, mysize.ws_row-5 , mysize.ws_col-2, 1, 1);
	wbkgd(*subtext, COLOR_PAIR(2));
	wattron(*subtext, A_BOLD);
	wprintw(*subtext, "\nOpen file to see text\n");
	wrefresh(*subtext);
	wrefresh(*text);
	return 0;
}

int control(WINDOW **twnd)
{
	int item = 0;
	keypad(*twnd, TRUE);
	cbreak();
	noecho();
	curs_set(FALSE);
	while((item = wgetch(*twnd) != KEY_F(3)))
	{
		switch(item)
		{
			case KEY_F(1):
					//openfile();
					break;
			case KEY_F(2):
					//savefile();
					//wprintw(tswnd, "\nF2!\n");
					break;
			case KEY_F(3):
					//wprintw(tswnd, "\nF3!\n");
					break;
		}
	}
	return 0;
}

int main()
{
	WINDOW *mwnd; //main window
	WINDOW *mswnd; //main sub
	WINDOW *twnd;	//text window
	WINDOW *tswnd; //text sub
	int fd = 0;
	initscr();
	signal(SIGWINCH, sig_winch);
	refresh();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	menuwindow(&mwnd, &mswnd);
	textwindow(&twnd, &tswnd);
	control(&twnd);

	refresh();

	delwin(tswnd);
	delwin(twnd);
	delwin(mswnd);
	delwin(mwnd);
	endwin();
	return 0;
}
