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
#define SLIDER_WIDTH 3
#define GROUP_WIDTH 5

#define FILL_CHARACTER ACS_CKBOARD
#define CLEAR_CHARACTER ' '
#define MUTED_CHARACTER 'M'
#define UNMUTED_CHARACTER 'U'

#define INCREASE_STEP 1
#define DECREASE_STEP -1

#define QUIT_KEY 'q'
#define INCREASE_KEY KEY_UP
#define DECREASE_KEY KEY_DOWN
#define SELECT_LEFT_KEY KEY_LEFT
#define SELECT_RIGHT_KEY KEY_RIGHT
#define NEXT_MIXER_KEY KEY_F(2)
#define PREV_MIXER_KEY KEY_F(1)

#endif /* CONFIG_H */
