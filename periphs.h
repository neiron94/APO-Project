#ifndef PERIPHS_H

#define PERIPHS_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "mzapo_regs.h"
#include "constants.h"
#include "mzapo_parlcd.h"


/**
 *  Return true if red rotary selector is pressed, return false otherwise.
 */
bool is_red_pressed(unsigned char *mem_base);

/**
 *  Return true if green rotary selector is pressed, return false otherwise.
 */
bool is_green_pressed(unsigned char *mem_base);

/**
 *  Return true if blue rotary selector is pressed, return false otherwise.
 */
bool is_blue_pressed(unsigned char *mem_base);

/**
 *  Send frame buffer to the parlcd display.
 */
void render_display(unsigned char *parlcd_mem_base, unsigned short *fb);

/**
 *  Fill parlcd display with zeroes.
 */
void clean_display(unsigned char *parlcd_mem_base);

/**
 *  Light RGB LED with the given color for the given amount of time (in seconds). 
 */
void light_rgb(unsigned char *mem_base, int time, uint32_t color);

#endif // PERIPHS_H