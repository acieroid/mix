#include "control.h"
#include "group.h"
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
  MixGroup *mixgroup;

  fd = mix_open_dev("/dev/mixer");
  mixer = mix_get_mixer(fd, 0);
  /*ext = mix_mixer_find_extension(mixer, "vmix0-outvol");*/
  mixgroup = mix_mixer_find_group(mixer, "jack.pink");

  init_ncurses();
  refresh();
  /*Control *control = control_new(ext, 0, 0, LINES);*/
  /*control_draw(control);*/
  Group *group = group_new(mixgroup, 1, 1, LINES);
  group_draw(group);

  while (ch != QUIT_KEY) {
    ch = getch();
    if (ch == KEY_UP) {
      group_increase(group);
    }
    else if (ch == KEY_DOWN) {
      group_decrease(group);
    }
    group_update(group);
    group_draw(group);
  }

  group_free(group);
  mix_mixer_free(mixer);
  exit_ncurses();
  return 0;
}
