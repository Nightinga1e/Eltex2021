#include "openfile.h"

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
	if(-1 == *fd)
	{
		noecho();
		cbreak();
		return -1;
	}
	readfile = read(*fd, text, TEXT_LEN);
	if(-1 == readfile)
	{
		noecho();
		cbreak();
		return -2;
	}
	wclear(*tswnd);
	wmove(*tswnd, 0, 0);
	wprintw(*tswnd, "%s" , text);
	wmove(*tswnd, 0, 0);
	wrefresh(*tswnd);
	noecho();
	cbreak();
	return 0;
}
