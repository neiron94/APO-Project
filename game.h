#ifndef GAME_H

#define GAME_H

#include <time.h>
#include <stdbool.h>

#include "structures.h"
#include "constants.h"
#include "print.h"
#include "periphs.h"
#include "snake.h"
#include "images.h"


/**
 *  Start game loop.
 */
void goto_game(unsigned short *fb, periph_addrs_t *periph_addrs, images_t *images, int speed);

/**
 *  Render game frame.
 */
void draw_game(unsigned short *fb, unsigned char *parlcd_mem_base, images_t *images, fruit_t *fruit, snake_t *player, snake_t *enemy);

/**
 *  Do defeat actions and return to menu.
 */
void defeat_action(unsigned short *fb, periph_addrs_t *periph_addrs);

/**
 *  Do victory actions and return to menu.
 */
void victory_action(unsigned short *fb, periph_addrs_t *periph_addrs);

#endif //GAME_H