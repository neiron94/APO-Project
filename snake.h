#ifndef SNAKE_H

#define SNAKE_H

#include <stdbool.h>
#include <stdint.h>

#include "mzapo_regs.h"
#include "structures.h"
#include "game.h"
#include "periphs.h"

/**
 *  Create snake with head on the given position (x, y).
 */
void init_snake(snake_t *snake, int x, int y);

/**
 *  If blue rotary selector is pressed, turn player's head right.
 * If green rotary selector is pressed, turn player's head left.
 */
void turn_head_player(unsigned char *mem_base, snake_t *player);

/**
 *  Turn enemy's head to fruit.
 */
void turn_head_enemy(snake_t *enemy, fruit_t *fruit);

/**
 *  Add new tile to snake tiles, if fruit was eaten.
 */
void grow(snake_t *snake);

/**
 *  Move all snake tiles.
 */
void move(snake_t *snake);

/**
 *  Return true if colision is detected, return false otherwise.
 */
bool is_colision(unsigned short *fb, periph_addrs_t *periph_addrs, snake_t *player, snake_t *enemy);

/**
 *  Set snake.ate_fruit to true, if head is on the fruit position.
 */
void eat_fruit(snake_t *player, snake_t *enemy, fruit_t *fruit);

/**
 *  Change directions of all snake tiles starting from the tail.
 */
void change_tiles_dir(snake_t *snake);

#endif // SNAKE_H