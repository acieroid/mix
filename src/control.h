#ifndef CONTROL_H
#define CONTROL_H

#include <ncurses.h>
#include <libmix.h>

#define CONTROL_WIDTH 3
#define FILL_CHARACTER ACS_CKBOARD /* or "#" */

/**
 * A control is the GUI element that controls an extension
 */
typedef struct {
  WINDOW *win;
  MixExtension *ext;
  int x;
  int y;
  int height;
} Control;

/**
 * @return a newly allocated control
 */
Control *control_new(MixExtension *ext, int x, int y, int height);

/**
 * free a control
 */
void control_free(Control *control);

/**
 * Update the value of a control
 */
void control_update(Control *control);

/**
 * Draw a control on the screen
 */
void control_draw(Control *control);

#endif /* CONTROL_H */
