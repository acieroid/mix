#include "control.h"

#include <stdio.h>
#include <ncurses.h>

void init_ncurses()
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
}

void exit_ncurses()
{
  endwin();
}

int main(int argc, char *argv[])
{
  init_ncurses();
  refresh();
  Control *control = control_new(NULL, 10, 0, LINES);
  control_draw(control);
  getch();

  exit_ncurses();
  return 0;
}
