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
	wprintw(*mswnd, " F2 - open file		F3 - edit file		F4 - save file		F5 - exit \n");
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
		noecho();
		cbreak();
		return -1;
	}
	readfile = read(*fd, text, TEXT_LEN);
	if (readfile == -1) 
	{
		noecho();
		cbreak();
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

int savefile(WINDOW **tswnd, int *fd)
{
	int row = 0;
	int col = 0;
	chtype buf;
	getmaxyx(*tswnd, row, col);
	lseek(*fd, 0, SEEK_SET);
	for(int i = 0; i <row; i++)
		for(int j = 0; j < col; j++)
		{
			buf = mvwinch(*tswnd, i, j);
			write(*fd, &buf, 1);
		}
	wmove(*tswnd, 0, 0);
	return 0;
}

int control(WINDOW **twnd, WINDOW **tswnd)
{
	int item = 0;
	static int fd = 0;
	int row = 0;
	int col = 0;
	int mrow = 0;
	int mcol = 0;
	int editfl = 0;
	keypad(*twnd, TRUE);
	cbreak();
	noecho();
	curs_set(FALSE);
	while((item != KEY_F(5)))
	{
		if(1 == editfl)
		{
			getyx(*tswnd, row, col);
		}	
		item = wgetch(*twnd);
		switch(item)
		{
			case KEY_F(2):
					wclear(*tswnd);
					wrefresh(*tswnd);
					if(0 != fd) 
					{
						close(fd);
						editfl = 0;
						row = 0;
						col = 0;
					}
					openfile(tswnd, &fd);
					break;
			case KEY_F(3):
					if(1 == editfl)
					{
						editfl = 0;
						break;
					}
					if((0 != fd) && (-1 != -fd) && (0 == editfl))
					{
						editfl = 1;
						getyx(*tswnd, row, col);
						getmaxyx(*tswnd, mrow, mcol);
					}
					break;
			case KEY_F(4):
					if((0 != fd)&&(-1 != fd))
					{
						savefile(tswnd, &fd);
					}					
					break;
			case KEY_F(5):
					break;
			case KEY_UP:
					if(0 != row)
					{
						wmove(*tswnd, row-1, col);
					} 
					break;
			case KEY_DOWN:
					if(mrow!= row)
					{
						wmove(*tswnd, row+1, col);
					}
					break;
			case KEY_LEFT:
					if(0 != col)
					{
						wmove(*tswnd, row, col-1);
					}
					break;
			case KEY_RIGHT:
					if(mcol != col)
					{
						wmove(*tswnd, row, col+1);
					}
					break;
			case KEY_BACKSPACE:
					if(1 == editfl)
					{
						if((0 == row)&&(0 == col)) break;
						wmove(*tswnd, row, col-1);
						waddch(*tswnd, ' ');
						wmove(*tswnd, row, col-1);
						wrefresh(*tswnd);
					}
					break;
			default:
					if(1 == editfl)
					{
						waddch(*tswnd, item);	
					}
					break;
		}
		wrefresh(*tswnd);
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
