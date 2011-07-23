#include "manager.h"
#include "config.h"

#include <stdio.h>
#include <ncurses.h>

void init_ncurses()
{
  initscr();
  init_colors();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0); /* cursor invisible */
}

void exit_ncurses()
{
  endwin();
}

Manager *next_manager(MixList *list, Manager *selected)
{
  return mix_list_select_right(list, (void *) selected);
}

Manager *prev_manager(MixList *list, Manager *selected)
{
  return mix_list_select_left(list, (void *) selected);
}

int main(int argc, char *argv[])
{
  int ch = 0;
  MixAPIFD fd;
  MixList *mixers = NULL, *managers = NULL, *iterator = NULL;
  Manager *selected = NULL;

  init_ncurses();
  fd = mix_open_dev("/dev/mixer");
  mixers = mix_get_mixers(fd);
  mix_foreach(iterator, mixers) {
    managers = mix_list_prepend(managers,
                                (void *) manager_new(iterator->data,
                                                     0, 1, LINES-1));
    if (selected == NULL)
      selected = managers->data; /* select the first mixer */
  }
  managers = mix_list_reverse(managers);

  refresh();
  manager_draw(selected);

  while (ch != QUIT_KEY) {
    /* handle key press */
    ch = getch();
    if (ch == NEXT_MIXER_KEY)
      selected = next_manager(managers, selected);
    else if (ch == PREV_MIXER_KEY)
      selected = prev_manager(managers, selected);
    manager_key_pressed(selected, ch);

    /* and redraw */
    clear();
    refresh();
    manager_draw(selected);
  }

  mix_list_free(managers, (MixFreeFunc) manager_free);
  mix_list_free(mixers, (MixFreeFunc) mix_mixer_free);
  exit_ncurses();
  return 0;
}
