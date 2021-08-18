#include <curses.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME_LEN 100
#define TEXT_LEN 3000

int openfile(WINDOW **, int *);
