#include "control.h"

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
