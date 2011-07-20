#include "control.h"
#include "group.h"
#include "colors.h"

#include <stdio.h>
#include <ncurses.h>

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
  MixGroup *mixgroup;

  fd = mix_open_dev("/dev/mixer");
  mixer = mix_get_mixer(fd, 0);
  /* TODO: create a manager for each mixer, not only the first one */
  manager = manager_new(mixer);

  init_ncurses();
  refresh();

  while (ch != QUIT_KEY) {
    ch = getch();
    manager_key_pressed(ch);
  }

  group_free(group);
  mix_mixer_free(mixer);
  exit_ncurses();
  return 0;
}
