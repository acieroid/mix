/**
 * @file control.h
 * @brief Implements the controls
 */
#ifndef CONTROL_H
#define CONTROL_H

#include <ncurses.h>
#include <libmix.h>

#define CONTROL_WIDTH 3
#define FILL_CHARACTER ACS_CKBOARD
#define CLEAR_CHARACTER ' '
#define INCREASE_STEP 1
#define DECREASE_STEP -1

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
 * Change the value of a control of @step
 */
void control_change_value(Control *control, int step);

/**
 * Increase the value of a control
 */
void control_increase(Control *control);

/**
 * Decrease the value of a control
 */
void control_decrease(Control *control);

/**
 * Draw a control on the screen
 */
void control_draw(Control *control);

#endif /* CONTROL_H */
