#include "stcur.h"
#include <string.h>

#define MAX_LEN 15

void get_password(WINDOW *win, char *password, int max_len)
{
	int i = 0;
	int ch;
	while(((ch = wgetch(win)) != 10) && (i< max_len-1))
	{
		if (ch==KEY_BACKSPACE)
		{
			int x, y;
			if (i==0) continue;
			getyx(win, y, x);
			mvwaddch(win, y, x-1, ' ');
			wrefresh(win);
			wmove(win, y, x-1);
			i--;
			continue;
		}
		password[i++] = ch;
		//wechochar(win, '*');
	}
	password[i] = 0;
	wechochar(win, '\n');
}


int main()
{
	WINDOW *wnd;
	char pass[15] = " ";
	const char RIGHT_PASSWORD[15] = "dipass";	
	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(TRUE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd = newwin(5, 23, 2, 2);
	wbkgd(wnd, COLOR_PAIR(1));
	wattron(wnd, A_BOLD);
	keypad(wnd, TRUE);
	wprintw(wnd, "Enter password...\n");
	get_password(wnd, pass, MAX_LEN);
	wattron(wnd, A_BLINK);
	if (strcmp(pass, RIGHT_PASSWORD) == 0)
		{
			wprintw(wnd, "ACCESS GRANTED!");
		}else{
			wprintw(wnd, "ACCESS DENIED!");
		}
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
