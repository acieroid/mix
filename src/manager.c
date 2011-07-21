#include "manager.h"
#include "group.h"
#include "control.h"
#include "config.h"

#include <assert.h>

#include <stdio.h>
Manager *manager_new(MixMixer *mixer)
{
  MixList *iterator;
  Group *group;
  Manager *manager = malloc(sizeof(*manager));
  assert(manager != NULL);

  /* create the groups */
  manager->groups = NULL;
  manager->selected = NULL;
  mix_foreach(iterator, mix_mixer_get_groups(mixer)) {
    printw("alo");
    group = group_new(iterator->data, 0, 1, LINES-1);
    if (manager->selected == NULL)
      manager->selected = group; /* select the first group */
    manager->groups = mix_list_prepend(manager->groups, (void *) group);
  }
  manager->groups = mix_list_reverse(manager->groups);

  return manager;
}

void manager_free(Manager *manager)
{
  assert(manager != NULL);
  free(manager);
}

void manager_select_left(Manager *manager)
{
  MixList *iterator;
  Group *prev = NULL;
  assert(manager != NULL);
  mix_foreach(iterator, manager->groups) {
    if (iterator->data == manager->selected) {
      if (prev == NULL)
        return; /* the most-left element is already selected */
      else
        manager->selected = prev;
      break;
    }
    prev = iterator->data;
  }
}

void manager_select_right(Manager *manager)
{
  MixList *iterator;
  assert(manager != NULL);
  mix_foreach(iterator, manager->groups) {
    if (iterator->data == manager->selected) {
      if (iterator->next == NULL)
        return; /* the most-right element is already selected */
      else
        manager->selected = iterator->next->data;
      break;
    }
  }
}

void manager_key_pressed(Manager *manager, int key)
{
  assert(manager != NULL);
  switch (key) {
  case SELECT_LEFT_KEY:
    manager_select_left(manager);
    break;
  case SELECT_RIGHT_KEY:
    manager_select_right(manager);
    break;
  case INCREASE_KEY:
    group_increase(manager->selected);
    break;
  case DECREASE_KEY:
    group_decrease(manager->selected);
    break;
  default:
    break;
  }
}

void manager_draw(Manager *manager)
{
  MixList *iterator;
  Group *group;
  int pos = 0;

  assert(manager != NULL);

  /* Draw the list of groups */
  move(0, 0);
  mix_foreach(iterator, manager->groups) {
    /* TODO: draw only until we go to the next line */
    group = iterator->data;
    if (group == manager->selected)
      attron(A_BOLD);
    printw("%s", group_get_name(group));
    if (group == manager->selected)
      attroff(A_BOLD);

    if (iterator->next != NULL)
      printw(" - ");
  }

  /* Draw the selected group */
  group_draw(manager->selected);
}
