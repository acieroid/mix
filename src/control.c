#include "control.h"
#include "colors.h"
#include "config.h"

#include <assert.h>
#include <string.h>
#include <math.h>

Control *control_new(MixExtension *ext, int x, int y, int height)
{
  int i;
  Control *control = malloc(sizeof(*control));
  assert(control != NULL);
  control->ext = ext;
  control->width = strlen(mix_extension_get_name(ext));
  if (mix_extension_is_mute(ext)) {
    control->width = max(control->width, MUTE_WIDTH);
    control->win = newwin(height-2, MUTE_WIDTH, y, x + control->width/2 - MUTE_WIDTH/2);
  }
  else if (mix_extension_is_slider(ext)) {
    control->width = max(control->width, SLIDER_WIDTH);

    control->win = newwin(height-2, SLIDER_WIDTH, y, x + control->width/2 - SLIDER_WIDTH/2);
  }
  else if (mix_extension_is_enum(ext)) {
    for (i = 0; i < mix_extension_get_max_value(ext); i++)
      control->width = max(control->width,
                           strlen(mix_extension_get_enum_values(ext)[i]) + 2);
    control->win = newwin(mix_extension_get_max_value(ext) + 2, control->width,
                          height - mix_extension_get_max_value(ext) - 2, x);
  }
  control->x = x;
  control->y = y;
  control->height = height;
  control->selected = 0;
  return control;
}

void control_free(Control *control)
{
  assert(control != NULL);
  if (control->win)
    delwin(control->win);
  free(control);
  /* the free of the extension associated with this control should not
     be handled here */
}

int control_width(Control *control)
{
  assert(control != NULL);
  return control->width;
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
  if (mix_extension_is_enum(control->ext))
    control_change_value(control, -1);
  else
    control_change_value(control, INCREASE_STEP);
}

void control_decrease(Control *control)
{
  if (mix_extension_is_enum(control->ext))
    control_change_value(control, 1);
  else
    control_change_value(control, DECREASE_STEP);
}

void control_mute(Control *control, int muted)
{
  assert(control != NULL);
  mix_extension_set_muted(control->ext, muted);
}

void control_select(Control *control)
{
  assert(control != NULL);
  control->selected = 1;
}

void control_unselect(Control *control)
{
  assert(control != NULL);
  control->selected = 0;
}

void control_set_color(Control *control, int color)
{
  assert(control != NULL);
  wattron(control->win, COLOR_PAIR(color));
}

void control_clear_color(Control *control)
{
  assert(control != NULL);
  wattrset(control->win, 0); /* clear all the attributes */
}
  
void control_draw(Control *control)
{
  int x, y, val, percent;
  MixExtension *ext;
  assert(control != NULL);
  ext = control->ext;

  if (control->win != NULL) {
    if (mix_extension_is_mute(ext)) {
      if (mix_extension_muted(ext))
        mvwaddch(control->win, control->height-4, 1, MUTED_CHARACTER);
      else
        mvwaddch(control->win, control->height-4, 1, UNMUTED_CHARACTER);
    }
    else if (mix_extension_is_slider(ext)) {
      box(control->win, 0, 0);
      for (x = 1; x <= 2; x++) {
        if (mix_extension_is_stereo(ext)) {
          if (x == 1)
            val = mix_extension_get_left_value(control->ext);
          else
            val = mix_extension_get_right_value(control->ext);
        }
        else {
          val = mix_extension_get_value(control->ext);
        }
        val = ((float) val /
               (float) mix_extension_get_max_value(control->ext)) *
          (control->height-4);

        for (y = control->height-4; y > 0; y--) {
          percent = 100 - (((float) y / (float) (control->height-2)) * 100);
          if (y > control->height-4-val) {
            control_set_color(control, (percent < 25) ? GREEN : ((percent > 75) ? RED : WHITE));
            mvwaddch(control->win, y, x, FILL_CHARACTER);
          }
          else {
            control_clear_color(control);
            mvwaddch(control->win, y, x, CLEAR_CHARACTER);
          }
        }
      }
      control_clear_color(control);
    }
    else if (mix_extension_is_enum(ext)) {
      box(control->win, 0, 0);
      for (y = 0; y < mix_extension_get_max_value(ext); y++) {
        if (strcmp(mix_extension_get_enum_values(ext)[y],
                   mix_extension_get_enum_value(ext)) == 0)
          wattron(control->win, A_REVERSE);
        /* TODO: handle unavailable enum values */
        x = control->width/2 - strlen(mix_extension_get_enum_values(ext)[y])/2;
        /* draw in the reverse order */
        mvwprintw(control->win, y+1,
                  max(x, 1),
                  "%s", mix_extension_get_enum_values(ext)[y]);
        wattroff(control->win, A_REVERSE);
      }
    }
    if (control->selected)
      attron(A_BOLD);
    mvprintw(control->y + control->height-1, control->x,
             "%s", mix_extension_get_name(ext));
    if (control->selected)
      attroff(A_BOLD);

    wrefresh(control->win);
  }
}
