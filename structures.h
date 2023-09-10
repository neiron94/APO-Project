#ifndef STRUCTURES_H

#define STRUCTURES_H

#include "constants.h"

#include <stdint.h>
#include <stdbool.h>


#define OPTIONS_COUNT 3

/**
 *  Menu options.
 */
enum options {
    NONE = -1, PLAY = 0, SPEED = 1, EXIT = 2
};

#define DIRS_COUNT 4

/**
 *  Directions.
 */
enum directions {
    UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
};

/**
 * Contains all peripherals addrsses.
 */
typedef struct {
    unsigned char *parlcd_mem_base;
    unsigned char *mem_base;
} periph_addrs_t;

/**
 * One tile of the snake.
 */
typedef struct {
    int x;
    int y;
    int dir;
} snake_tile_t;

/**
 * Snake which consists of tiles.
 */
typedef struct {
    int size;
    bool ate_fruit;
    snake_tile_t tiles[MAX_SIZE];
} snake_t;

/**
 * Fruit that can be eaten by snake.
 */
typedef struct {
    int x;
    int y;
} fruit_t;

/**
 * Contains all images.
 */
typedef struct {
    uint16_t menu_background[SCREEN_WIDTH * SCREEN_HEIGHT];
    uint16_t button[BUTTON_W * BUTTON_H];
    uint16_t button_active[BUTTON_W * BUTTON_H];
    uint16_t game_background[SCREEN_WIDTH * SCREEN_HEIGHT];
    uint16_t fruit[TILE_SIZE * TILE_SIZE];
    uint16_t snake1_head[TILE_SIZE * TILE_SIZE * 4];
    uint16_t snake2_head[TILE_SIZE * TILE_SIZE * 4];
    uint16_t snake1_tail[TILE_SIZE * TILE_SIZE * 4];
    uint16_t snake2_tail[TILE_SIZE * TILE_SIZE * 4];
    uint16_t snake1_body[TILE_SIZE * TILE_SIZE * 6];
    uint16_t snake2_body[TILE_SIZE * TILE_SIZE * 6];
} images_t;


#endif // STRUCTURES_H
