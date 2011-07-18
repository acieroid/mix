#include "control.h"

#include <assert.h>

Control *control_new(MixExtension *ext, int x, int y, int height)
{
  Control *control = malloc(sizeof(*control));
  assert(control != NULL);
  control->ext = ext;
  control->win = newwin(height, CONTROL_WIDTH, y, x);
  box(control->win, 0, 0);
  control->x = x;
  control->y = y;
  control->height = height;
  return control;
}

void control_free(Control *control)
{
  assert(control != NULL);
  delwin(control->win);
  free(control);
  /* the free of the extension associated with this control should not
     be handled here */
}

void control_update(Control *control)
{
  assert(control != NULL);
  mix_extension_update_value(control->ext);
}

void control_draw(Control *control)
{
  assert(control != NULL);

  int x, y;
  x = control->x;
  for (y = control->y + control->height - 3; y > control->y - 1; y--) {
    mvwaddch(control->win, y, x, FILL_CHARACTER);
  }
  wrefresh(control->win);
}
