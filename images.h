#ifndef IMAGES_H

#define IMAGES_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "constants.h"
#include "print.h"

/**
 *  Load all images.
 */
void load_images(images_t *images);

/**
 *  Load one image from .ppm file.
 */
void load_image(uint16_t *img, char *file_name, int img_count, int img_size);

/**
 *  Write button image to frame buffer.
 */
void draw_button(unsigned short *fb, uint16_t *button_img, int x, int y, char *word);

/**
 *  Write fruit image to frame buffer.
 */
void draw_fruit(unsigned short *fb, uint16_t *fruit_img, fruit_t *fruit);

/**
 *  Write background image (menu/game) to frame buffer.
 */
void draw_background(unsigned short *fb, uint16_t *img);

/**
 *  Write all images of all snake tiles to frame buffer.
 */
void draw_snake(unsigned short *fb, images_t *images, snake_t *snake, bool is_player_snake);

/**
 *  Write head image to frame buffer.
 */
void draw_head(unsigned short *fb, uint16_t *head_img, snake_tile_t head);

/**
 *  Write tail image to frame buffer.
 */
void draw_tail(unsigned short *fb, uint16_t *tail_img, snake_tile_t tail);

/**
 *  Write one body tile image to frame buffer.
 */
void draw_body(unsigned short *fb, uint16_t *body_img, snake_tile_t cur_tile, snake_tile_t next_tile);

#endif // IMAGES_H