#ifndef CONTROL_H
#define CONTROL_H

#include <ncurses.h>
#include <libmix.h>

/**
 * A control is the GUI element that controls an extension
 */
typedef struct {
  WINDOW *win;
  MixExtension *ext;
} Control;

/**
 * @return a newly allocated control
 */
Control *control_new(MixExtensions *ext);

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
