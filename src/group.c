#include "group.h"
#include "config.h"

Group *group_new(MixGroup *mixgroup, int x, int y, int height)
{
  MixList *iterator;
  MixExtension *ext;
  Group *group = malloc(sizeof(*group));
  assert(group != NULL);
  group->group = mixgroup;
  group->win = newwin(height, GROUP_WIDTH, y, x);

  group->mute = NULL;
  group->slider = NULL;
  mix_foreach(iterator, mix_group_get_extensions(mixgroup)) {
    ext = iterator->data;
    if (mix_extension_is_mute(ext) && group->mute == NULL)
      group->mute = control_new(ext, x, y, height-1);
    else if (mix_extension_is_slider(ext) && group->slider == NULL)
      group->slider = control_new(ext, x, height-1, 1);
  }
  return group;
}

void group_free(Group *group)
{
  assert(group != NULL);
  delwin(group->win);
  if (group->slider != NULL)
    control_free(group->slider);
  if (group->mute != NULL)
    control_free(group->mute);
  free(group);
}

void group_update(Group *group)
{
  if (group->slider != NULL)
    control_update(group->slider);
  if (group->mute != NULL)
    control_update(group->mute);
}

void group_increase(Group *group)
{
  if (group->slider != NULL)
    control_increase(group->slider);
}

void group_decrease(Group *group)
{
  if (group->slider != NULL)
    control_decrease(group->slider);
}

void group_mute(Group *group, int muted)
{
  if (group->mute != NULL)
    control_mute(group->mute, muted);
}

void group_draw(Group *group)
{
  if (group->slider != NULL)
    control_draw(group->slider);
  if (group->mute != NULL)
    control_draw(group->mute);
}
