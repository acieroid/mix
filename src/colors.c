#include "colors.h"

void init_colors()
{
  if (has_colors() == TRUE) {
    start_color();
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(RED, COLOR_RED, COLOR_RED);
  }
}
