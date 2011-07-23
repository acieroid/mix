#include "group.h"
#include "config.h"

Group *group_new(MixGroup *mixgroup, int x, int y, int height)
{
  int most_right_x = 0;
  MixList *iterator;
  MixExtension *ext;
  Control *control;
  Group *group = malloc(sizeof(*group));
  assert(group != NULL);
  group->group = mixgroup;

  group->groups = NULL;
  mix_foreach(iterator, mix_group_get_groups(mixgroup)) {
    group->groups = mix_list_prepend(group->groups,
                                     (void *) group_new(iterator->data,
                                                        x, y+1, height-1));
  }
  group->groups = mix_list_reverse(group->groups);

  group->controls = NULL;
  mix_foreach(iterator, mix_group_get_extensions(mixgroup)) {
    ext = iterator->data;
    control = control_new(ext, most_right_x, y+1, height-2);
    most_right_x += control_width(control) + 1;

    group->controls = mix_list_prepend(group->controls, (void *) control);
  }
  group->controls = mix_list_reverse(group->controls);

  group->x = x;
  group->y = y;
  group->height = height;
  group->width = most_right_x;
  group->selected = NULL;

  return group;
}

void group_free(Group *group)
{
  assert(group != NULL);
  mix_list_free(group->groups, (MixFreeFunc) group_free);
  mix_list_free(group->controls, (MixFreeFunc) control_free);
  free(group);
}

void group_update(Group *group)
{
  mix_list_iter(group->groups, (MixIterFunc) group_update);
  mix_list_iter(group->controls, (MixIterFunc) control_update);
}

void group_increase(Group *group)
{
  /* TODO */
}

void group_decrease(Group *group)
{
  /* TODO */
}

void group_mute(Group *group, int muted)
{
  /* TODO */
}

void group_start_select(Group *group)
{
  assert(group != NULL);
  group->selected = group->groups->data;
}

void group_stop_select(Group *group)
{
  assert(group != NULL);
  group->selected = NULL;
}

void group_select_left(Group *group)
{
  assert(group != NULL);
  group->selected = (Group *) mix_list_select_left(group->groups,
                                                   (void *) group->selected);
}

void group_select_right(Group *group)
{
  assert(group != NULL);
  group->selected = (Group *) mix_list_select_right(group->groups,
                                                    (void *) group->selected);
}

void group_key_pressed(Group *group, int key)
{
  switch (key) {
  case SELECT_LEFT_KEY:
    group_select_left(group);
    break;
  case SELECT_RIGHT_KEY:
    group_select_right(group);
    break;
  }
}

void group_draw(Group *group)
{
  MixList *iterator;
  assert(group != NULL);

  /* draw the list of sub-groups */
  move(group->y, group->x);
  mix_foreach(iterator, group->groups) {
    if (iterator->data == group->selected)
      attron(A_BOLD);
    printw("%s", group_get_name(iterator->data));
    if (iterator->data == group->selected)
      attroff(A_BOLD);
    if (iterator->next != NULL)
      printw(" - ");
  }
  
  if (group->controls != NULL) /* if the groups has controls */
    mix_list_iter(group->controls, (MixIterFunc) control_draw);
}

char *group_get_name(Group *group)
{
  assert(group != NULL);
  return mix_group_get_name(group->group);
}
