#include "images.h"


void load_images(images_t *images) {
    load_image(images->game_background, GAME_BACK_IMG, 1, SCREEN_WIDTH * SCREEN_HEIGHT);
    load_image(images->menu_background, MENU_BACK_IMG, 1, SCREEN_WIDTH * SCREEN_HEIGHT);
    load_image(images->button, BUTTON_IMG, 1, BUTTON_W * BUTTON_H);
    load_image(images->button_active, BUTTON_ACTIVE_IMG, 1, BUTTON_W * BUTTON_H);
    load_image(images->fruit, FRUIT_IMG, 1, TILE_SIZE * TILE_SIZE);
    load_image(images->snake1_head, SNAKE_1_HEAD_IMG, 4, TILE_SIZE * TILE_SIZE);
    load_image(images->snake2_head, SNAKE_2_HEAD_IMG, 4, TILE_SIZE * TILE_SIZE);
    load_image(images->snake1_tail, SNAKE_1_TAIL_IMG, 4, TILE_SIZE * TILE_SIZE);
    load_image(images->snake2_tail, SNAKE_2_TAIL_IMG, 4, TILE_SIZE * TILE_SIZE);
    load_image(images->snake1_body, SNAKE_1_BODY_IMG, 6, TILE_SIZE * TILE_SIZE);
    load_image(images->snake2_body, SNAKE_2_BODY_IMG, 6, TILE_SIZE * TILE_SIZE);
}


void load_image(uint16_t *img, char *file_name, int img_count, int img_size) {
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        fprintf(stderr, "Can't read image from %s", file_name);
        exit(1);
    }

    // Eat service information of .ppm file
    for (int i = 0; i < 4; i++)
        while(fgetc(file) != '\n')  
            continue;

    // img_count represents count of images in one .ppm file
    for (int k = 0; k < img_count; k++) {
        for (int i = 0; i < img_size; i++) {
            uint8_t r = fgetc(file);
            uint8_t g = fgetc(file);
            uint8_t b = fgetc(file);
            img[k * img_size + i] = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3); // rgb888 -> rgb565
        }
    }

    fclose(file);
}


void draw_button(unsigned short *fb, uint16_t *button_img, int x, int y, char *word) {
  int offset = y * SCREEN_WIDTH + x;
  
  for (int i = 0; i < BUTTON_H; i++)
    for (int j = 0; j < BUTTON_W; j++)
      fb[offset + i * SCREEN_WIDTH + j] = button_img[i * BUTTON_W + j];

  print_word(fb, word, x + WORD_OFFSET_X, y + WORD_OFFSET_Y, WORD_COLOR, MENU_SCALE);
}


void draw_fruit(unsigned short *fb, uint16_t *fruit_img, fruit_t *fruit) {
  int offset = fruit->y * TILE_SIZE * SCREEN_WIDTH + fruit->x * TILE_SIZE;
  
  for (int i = 0; i < TILE_SIZE; i++)
    for (int j = 0; j < TILE_SIZE; j++)
      fb[offset + i * SCREEN_WIDTH + j] = fruit_img[i * TILE_SIZE + j];
}


void draw_background(unsigned short *fb, uint16_t *img) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        fb[i]=img[i];
}


void draw_snake(unsigned short *fb, images_t *images, snake_t *snake, bool is_player_snake) {
    for (int k = 0; k < snake->size; k++) {
        if (k == 0) {
            if (is_player_snake)    draw_head(fb, images->snake1_head, snake->tiles[k]);
            else                    draw_head(fb, images->snake2_head, snake->tiles[k]);
        }
        else if (k == snake->size - 1) {
            if (is_player_snake)    draw_tail(fb, images->snake1_tail, snake->tiles[k]);
            else                    draw_tail(fb, images->snake2_tail, snake->tiles[k]);
        }
        else {
            if (is_player_snake)    draw_body(fb, images->snake1_body, snake->tiles[k], snake->tiles[k + 1]);
            else                    draw_body(fb, images->snake2_body, snake->tiles[k], snake->tiles[k + 1]);
        }
    }
}


void draw_head(unsigned short *fb, uint16_t *head_img, snake_tile_t head) {
    int head_offset = head.dir * TILE_SIZE * TILE_SIZE;
    int fb_offset = head.y * TILE_SIZE * SCREEN_WIDTH + head.x * TILE_SIZE;

    for (int i = 0; i < TILE_SIZE; i++)
        for (int j = 0; j < TILE_SIZE; j++)
            fb[fb_offset + i * SCREEN_WIDTH + j] = head_img[head_offset + i * TILE_SIZE + j];
}


void draw_tail(unsigned short *fb, uint16_t *tail_img, snake_tile_t tail) {
    int tail_offset = tail.dir * TILE_SIZE * TILE_SIZE;
    int fb_offset = tail.y * TILE_SIZE * SCREEN_WIDTH + tail.x * TILE_SIZE;

    for (int i = 0; i < TILE_SIZE; i++)
        for (int j = 0; j < TILE_SIZE; j++)
            fb[fb_offset + i * SCREEN_WIDTH + j] = tail_img[tail_offset + i * TILE_SIZE + j];
}



void draw_body(unsigned short *fb, uint16_t *body_img, snake_tile_t cur_tile, snake_tile_t next_tile) {
    int body_offset = TILE_SIZE * TILE_SIZE;

    if ((cur_tile.dir == RIGHT && next_tile.dir == DOWN) || (cur_tile.dir == UP && next_tile.dir == LEFT))
        body_offset *= 0;
    else if ((cur_tile.dir == RIGHT && next_tile.dir == UP) || (cur_tile.dir == DOWN && next_tile.dir == LEFT))
        body_offset *= 1;
    else if ((cur_tile.dir == LEFT && next_tile.dir == UP) || (cur_tile.dir == DOWN && next_tile.dir == RIGHT))
        body_offset *= 2;
    else if ((cur_tile.dir == UP && next_tile.dir == RIGHT) || (cur_tile.dir == LEFT && next_tile.dir == DOWN))
        body_offset *= 3;
    else if ((cur_tile.dir == UP && next_tile.dir == UP) || (cur_tile.dir == DOWN && next_tile.dir == DOWN))
        body_offset *= 4;
    else if ((cur_tile.dir == RIGHT && next_tile.dir == RIGHT) || (cur_tile.dir == LEFT && next_tile.dir == LEFT))
        body_offset *= 5;


    int fb_offset = cur_tile.y * TILE_SIZE * SCREEN_WIDTH + cur_tile.x * TILE_SIZE;

    for (int i = 0; i < TILE_SIZE; i++)
        for (int j = 0; j < TILE_SIZE; j++)
            fb[fb_offset + i * SCREEN_WIDTH + j] = body_img[body_offset + i * TILE_SIZE + j];
}
