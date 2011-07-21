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

  group->controls = NULL;
  mix_foreach(iterator, mix_group_get_extensions(mixgroup)) {
    ext = iterator->data;
    control = control_new(ext, most_right_x, y, height);
    most_right_x += control_width(control) + 1;

    group->controls = mix_list_prepend(group->controls, (void *) control);
  }
  group->controls = mix_list_reverse(group->controls);

  group->win = newwin(height, most_right_x, y, x);
  return group;
}

void group_free(Group *group)
{
  assert(group != NULL);
  delwin(group->win);
  mix_list_free(group->controls, (MixFreeFunc) control_free);
  free(group);
}

void group_update(Group *group)
{
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

void group_draw(Group *group)
{
  mix_list_iter(group->controls, (MixIterFunc) control_draw);
}

char *group_get_name(Group *group)
{
  assert(group != NULL);
  return mix_group_get_name(group->group);
}
