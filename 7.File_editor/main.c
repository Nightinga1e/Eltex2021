#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "stcur.h"

#define FILENAME_LEN 100
#define TEXT_LEN 3000

struct winsize mysize;

int menuwindow(WINDOW **mwnd, WINDOW **mswnd)
{
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &mysize);
	*mwnd = newwin(3, mysize.ws_col, 0, 0);
	wattron(*mwnd, COLOR_PAIR(1));
	box(*mwnd, '#', '#');
	*mswnd = derwin(*mwnd, 1, mysize.ws_col-1, 1, 1);
	wbkgd(*mswnd, COLOR_PAIR(2));
	wattron(*mswnd, A_BOLD);
	wprintw(*mswnd, " F2 - open file		F3 - save file		F4 - exit \n");
	wrefresh(*mswnd);
	wrefresh(*mwnd);
	return 0;
}

int textwindow(WINDOW **twnd, WINDOW **tswnd)
{
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &mysize);
	*twnd = newwin(mysize.ws_row-3, mysize.ws_col, 3, 0);
	wattron(*twnd, COLOR_PAIR(1));
	box(*twnd, '#', '#');
	*tswnd = derwin(*twnd, mysize.ws_row-5 , mysize.ws_col-2, 1, 1);
	wbkgd(*tswnd, COLOR_PAIR(2));
	wattron(*tswnd, A_BOLD);
	wprintw(*tswnd, "\nOpen file to see text\n");
	wrefresh(*tswnd);
	wrefresh(*twnd);
	return 0;
}

int openfile(WINDOW **tswnd, int *fd)
{
	int readfile = 0;
	char filename[FILENAME_LEN] = " ";
	char text[TEXT_LEN] = " ";
	
	wclear(*tswnd);
	wrefresh(*tswnd);
	wmove(*tswnd, 0, 0);
	wprintw(*tswnd, "Enter name of file to open...\n");
	curs_set(TRUE);
	echo();
	nocbreak();
	wgetnstr(*tswnd, filename, FILENAME_LEN);
	*fd = open(filename, O_RDWR);
	if (-1 == *fd) 
	{
		return -1;
	}
	readfile = read(*fd, text, TEXT_LEN);
	if (readfile == -1) 
	{
		return -2;
	}
	wclear(*tswnd);
	wmove(*tswnd, 0, 0);
	wprintw(*tswnd, "%s", text);
	wmove(*tswnd, 0, 0);
	wrefresh(*tswnd);
	noecho();
	cbreak();
	return 0;
}
int control(WINDOW **twnd, WINDOW **tswnd)
{
	int item = 0;
	static int fd = 0;
	keypad(*twnd, TRUE);
	cbreak();
	noecho();
	curs_set(FALSE);
	while((item != KEY_F(4)))
	{
		item = wgetch(*twnd);
		switch(item)
		{
			case KEY_F(2):
					wclear(*tswnd);
					wrefresh(*tswnd);
					if(fd!=0) 
					{
						close(fd);
					}
					openfile(tswnd, &fd);
					break;
			case KEY_F(3):
					//savefile();
					//wprintw(tswnd, "\nF2!\n");
					break;
			case KEY_F(4):
					//wprintw(tswnd, "\nF3!\n");
					break;
		}
	}
	close(fd);
	return 0;
}

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
