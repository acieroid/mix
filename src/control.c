#include "control.h"
#include "colors.h"

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

void control_change_value(Control *control, int step)
{
  MixExtension *ext;
  assert(control != NULL);
  ext = control->ext;
  
  if (mix_extension_is_stereo(ext))
    mix_extension_set_stereo_value(ext,
                                   mix_extension_get_left_value(ext) + step,
                                   mix_extension_get_right_value(ext) + step);
  else
    mix_extension_set_value(ext,
                            mix_extension_get_value(ext) + step);
}

void control_increase(Control *control)
{
  control_change_value(control, INCREASE_STEP);
}

void control_decrease(Control *control)
{
  control_change_value(control, DECREASE_STEP);
}

void control_draw(Control *control)
{
  int y, val, percent;
  assert(control != NULL);

  val = ((float) mix_extension_get_value(control->ext) /
         (float) mix_extension_get_max_value(control->ext)) *
    (control->height-2);
  
  for (y = control->height-2; y > 0; y--) {
    percent = 100 - (((float) y / (float) (control->height-2)) * 100);
    if (y > control->height-2-val) {
      if (percent <= 25)
        wattron(control->win, COLOR_PAIR(GREEN_PAIR));
      else if (percent >= 75)
        wattron(control->win, COLOR_PAIR(RED_PAIR));
      else
        wattron(control->win, COLOR_PAIR(WHITE_PAIR));

      mvwaddch(control->win, y, 1, FILL_CHARACTER);
    }
    else {
      wattroff(control->win, COLOR_PAIR(GREEN_PAIR));
      wattroff(control->win, COLOR_PAIR(WHITE_PAIR));
      wattroff(control->win, COLOR_PAIR(RED_PAIR));
      mvwaddch(control->win, y, 1, CLEAR_CHARACTER);
    }
  }
  wrefresh(control->win);
}
