#ifndef DRAW_H

#define DRAW_H

#include "constants.h"
#include "structures.h"
#include "font_types.h"


/**
 *  Print arrow near the chosen button.
 */
void print_arrow(unsigned short *fb, int option, int scale);

/**
 *  Print word on the give nposition with the given color and scale.
 */
void print_word(unsigned short *fb, char *word, int x, int y, unsigned short color, int scale);

/**
 *  Write one pixel to the frame buffer.
 */
void draw_pixel(unsigned short *fb, int x, int y, unsigned short color);

/**
 *  Write big pixel to the frame buffer.
 */
void draw_pixel_big(unsigned short *fb, int x, int y, unsigned short color, int scale);

/**
 *  Count width of the character.
 */
int char_width(int ch);

/**
 *  Write one character.
 */
void print_char(unsigned short *fb, int x, int y, char ch, unsigned short color, int scale);

#endif // DRAW_H
