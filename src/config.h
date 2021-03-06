/**
 * @file config.h
 * @brief Contains all the constant definitions
 */

#ifndef CONFIG_H
#define CONFIG_H

#define max(a,b) ((a) > (b) ? (a) : (b))

#define GREEN 1
#define WHITE 2
#define RED 3

#define MUTE_WIDTH 5
#define SLIDER_WIDTH 4
#define GROUP_WIDTH 5

#define FILL_CHARACTER ACS_CKBOARD
#define CLEAR_CHARACTER ' '
#define MUTED_CHARACTER 'M'
#define UNMUTED_CHARACTER 'U'

/* TODO: enum shouldn't use those steps */
#define INCREASE_STEP 5
#define DECREASE_STEP -5

#define QUIT_KEY 'q'
#define INCREASE_KEY KEY_UP
#define DECREASE_KEY KEY_DOWN
#define SELECT_LEFT_KEY KEY_LEFT
#define SELECT_RIGHT_KEY KEY_RIGHT
#define SELECT_UP_KEY KEY_UP
#define SELECT_DOWN_KEY KEY_DOWN
#define NEXT_MIXER_KEY KEY_F(2)
#define PREV_MIXER_KEY KEY_F(1)
#define SELECT_CONTROL_KEY 10 /* enter key */
#define UNSELECT_CONTROL_KEY 127 /* backspace key */

#endif /* CONFIG_H */
