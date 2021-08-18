#include "savefile.h"

int savefile(WINDOW **tswnd, int *fd)
{
	int row = 0;
	int col = 0;
	chtype buf;
	getmaxyx(*tswnd, row, col);
	lseek(*fd, 0, SEEK_SET);
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			buf = mvwinch(*tswnd, i, j);
			write(*fd, &buf, 1);
		}
	}
	wmove(*tswnd, 0, 0);
	return 0;
}
