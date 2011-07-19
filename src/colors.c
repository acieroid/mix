#include "colors.h"

void init_colors()
{
  if (has_colors() == TRUE) {
    start_color();
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(WHITE_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK);
  }
}
