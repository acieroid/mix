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
  WINDOW *win;
  MixGroup *group;
  Control *mute;
  Control *slider;
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
 * Draw a group
 */
void group_draw(Group *group);


#endif
