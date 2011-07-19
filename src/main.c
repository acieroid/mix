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
  MixAPIFD fd;
  MixMixer *mixer;
  MixExtension *ext;
  fd = mix_open_dev("/dev/mixer");
  mixer = mix_get_mixer(fd, 0);
  ext = mix_mixer_find_extension(mixer, "vmix0-outvol");
  init_ncurses();
  refresh();
  Control *control = control_new(ext, 0, 0, LINES);
  control_draw(control);
  getch();

  exit_ncurses();
  return 0;
}
