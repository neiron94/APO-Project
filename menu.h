#ifndef MENU_H

#define MENU_H

#include <stdbool.h>

#include "structures.h"
#include "settings.h"
#include "constants.h"
#include "game.h"
#include "print.h"
#include "periphs.h"
#include "images.h"

/**
 *  Start menu, from which game can be started, speed can be set and program can be ended.
 */
void goto_menu(periph_addrs_t *periph_addrs, unsigned short *fb, images_t *images);

/**
 *  Draw menu panel with buttons.
 */
void draw_menu_panel(unsigned short *fb, unsigned char *parlcd_mem_base, images_t *images, int chosen_option, int active_button);

/**
 *  Update chosen button. If blue rotary selector is pressed, go to bottom button. 
 * If green rotary selector is pressed, go to top button.
 */
int update_choose(int currentOption, unsigned char *mem_base);

#endif // MENU_H
