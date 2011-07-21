/**
 * @file control.h
 * @brief Implements the controls
 */
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
  int x;
  int y;
  int width;
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
 * return the width of this control
 */
int control_width(Control *control);

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
 * Set the mute value of a control (1 = muted, 2 = unmuted)
 */
void control_mute(Control *control, int muted);

/**
 * Set a current color for the control
 */
void control_set_color(Control *control, int color);

/**
 * Clear the color of the control
 */
void control_clear_color(Control *control);

/**
 * Draw a control on the screen
 */
void control_draw(Control *control);

#endif /* CONTROL_H */
