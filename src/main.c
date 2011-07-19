#include "control.h"
#include "colors.h"

#include <stdio.h>
#include <ncurses.h>

#define QUIT_KEY 'q'

void init_ncurses()
{
  initscr();
  init_colors();
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
  int ch = 0;
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

  while (ch != QUIT_KEY) {
    ch = getch();
    if (ch == KEY_UP) {
      control_increase(control);
      control_update(control);
    }
    else if (ch == KEY_DOWN) {
      control_decrease(control);
      control_update(control);
    }
    control_draw(control);
  }

  exit_ncurses();
  return 0;
}
