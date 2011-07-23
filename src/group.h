/**
 * @file group.h
 * @brief Implements groups of controls (as is OSS groups)
 */
#ifndef GROUP_H
#define GROUP_H

#include "control.h"

#include <ncurses.h>
#include <libmix.h>

typedef struct {
  MixGroup *group;
  MixList *groups;
  MixList *controls;
  struct Group *selected;
  int x, y;
  int width, height;
} Group;

/**
 * @return a newly allocated group
 */
Group *group_new(MixGroup *group, int x, int y, int height);

/**
 * Free a group
 */
void group_free(Group *group);

/**
 * Update all the elements of a group
 */
void group_update(Group *group);

/**
 * Increase the slider element of a group
 */
void group_increase(Group *group);

/**
 * Decrease the slider element of a group
 */
void group_decrease(Group *group);

/**
 * Set the mute element of a group
 */
void group_mute(Group *group, int muted);

/**
 * Unmute the mute element of a group
 */
void group_unmute(Group *group);

/**
 * Select subgroup
 */
void group_select_down(Group *group);

/**
 * Unselect ungroup
 * @return 1 if there's no more parent groups
 */
int group_select_up(Group *group);

/**
 * Select the left subgroup
 */
void group_select_left(Group *group);

/**
 * Select the right subgroup
 */
void group_select_right(Group *group);

/**
 * Handle a key press
 */
void group_key_pressed(Group *group, int key);

/**
 * Draw a group
 */
void group_draw(Group *group);

/**
 * @return the name of this group
 */
char *group_get_name(Group *group);


#endif
