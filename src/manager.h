/**
 * @file manager.h
 * @brief Implements the group and control manager
 */
#ifndef MANAGER_H
#define MANAGER_H

#include "group.h"

#include <ncurses.h>
#include <libmix.h>

/**
 * The manager handles all the controls and groups of a mixer
 * @todo handle alone extensions (only extensions contained in groups
 * are handled right now)
 */
typedef struct {
  MixList *groups;
  Group *selected;
  int in_group_select;
} Manager;

/**
 * @return a newly allocated manager
 */
Manager *manager_new(MixMixer *mixer, int x, int y, int height);

/**
 * Free a manager
 */
void manager_free(Manager *manager);

/**
 * Select the left group
 */
void manager_select_left(Manager *manager);

/**
 * Select the right group
 */
void manager_select_right(Manager *manager);

/**
 * Handle a key press
 */
void manager_key_pressed(Manager *manager, int key);

/**
 * Draw each group and extensions of this manager
 */
void manager_draw(Manager *manager);


#endif /* MANAGER_H */
