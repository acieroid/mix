/**
 * @file colors.h
 * @brief Implements color-related routines
 */
#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

#define GREEN_PAIR 1
#define WHITE_PAIR 2
#define RED_PAIR 3

/**
 * Init everything related to the colors
 */
void init_colors();

#endif /* COLORS_H */
