#include "snake.h"


void init_snake(snake_t *snake, int x, int y) {
    snake->size = 3;

    snake_tile_t tile1 = {.x = x, .y = y, .dir = RIGHT};
    snake->tiles[0] = tile1;

    snake_tile_t tile2 = {.x = (x - 1 + TILES_IN_WIDTH) % TILES_IN_WIDTH, .y = y, .dir = RIGHT};
    snake->tiles[1] = tile2;

    snake_tile_t tile3 = {.x = (x - 2 + TILES_IN_WIDTH) % TILES_IN_WIDTH, .y = y, .dir = RIGHT};
    snake->tiles[2] = tile3;

    snake->ate_fruit = false;
}

void change_tiles_dir(snake_t *snake) {
    for (int i = snake->size - 1; i > 0; i--)
        snake->tiles[i].dir = snake->tiles[i - 1].dir;
}


void eat_fruit(snake_t *player, snake_t *enemy, fruit_t *fruit) {
    if (player->tiles[0].x == fruit->x && player->tiles[0].y == fruit->y) {
        fruit->x = rand() % TILES_IN_WIDTH;
        fruit->y = rand() % TILES_IN_HEIGHT;
        player->ate_fruit = true;
    }
    else if (enemy->tiles[0].x == fruit->x && enemy->tiles[0].y == fruit->y) {
        fruit->x = rand() % TILES_IN_WIDTH;
        fruit->y = rand() % TILES_IN_HEIGHT;
        enemy->ate_fruit = true;
    }
}

bool is_colision(unsigned short *fb, periph_addrs_t *periph_addrs, snake_t *player, snake_t *enemy) {
    // Check all player's tiles
    for (int i = 0; i < player->size; i++) {
        if (i != 0 && player->tiles[0].x == player->tiles[i].x && player->tiles[0].y == player->tiles[i].y) {
            defeat_action(fb, periph_addrs);
            return true;
        }
        else if (enemy->tiles[0].x == player->tiles[i].x && enemy->tiles[0].y == player->tiles[i].y) {
            victory_action(fb, periph_addrs);
            return true;
        }
    }

    // Check all enemys tiles
    for (int i = 0; i < enemy->size; i++) {
        if (i != 0 && enemy->tiles[0].x == enemy->tiles[i].x && enemy->tiles[0].y == enemy->tiles[i].y) {
            victory_action(fb, periph_addrs);
            return true;
        }
        else if (player->tiles[0].x == enemy->tiles[i].x && player->tiles[0].y == enemy->tiles[i].y) {
            defeat_action(fb, periph_addrs);
            return true;
        }
    }

    return false;
}



void turn_head_player(unsigned char *mem_base, snake_t *player) {
    if (is_blue_pressed(mem_base))
        player->tiles[0].dir = (player->tiles[0].dir + 1) % DIRS_COUNT;
    if (is_green_pressed(mem_base))
        player->tiles[0].dir = (player->tiles[0].dir - 1 + DIRS_COUNT) % DIRS_COUNT;
}


void turn_head_enemy(snake_t *enemy, fruit_t *fruit) {
    int head_x = enemy->tiles[0].x;
    int head_y = enemy->tiles[0].y;
    int head_dir = enemy->tiles[0].dir;
    
    if (head_x < fruit->x && head_dir != LEFT)
        enemy->tiles[0].dir = RIGHT;
    else if (head_x > fruit->x && head_dir != RIGHT)
        enemy->tiles[0].dir = LEFT;
    else if (head_y < fruit->y && head_dir != UP)
        enemy->tiles[0].dir = DOWN;
    else if (head_y > fruit->y && head_dir != DOWN)
        enemy->tiles[0].dir = UP;   
}


void grow(snake_t *snake) {
    int tail_index = snake->size - 1;
    if (snake->ate_fruit && snake->size < MAX_SIZE) {
        snake_tile_t new_tile = {.x = snake->tiles[tail_index].x, .y = snake->tiles[tail_index].y, .dir = snake->tiles[tail_index].dir};
        snake->tiles[tail_index + 1] = new_tile;
        snake->size++;
    }
}


void move(snake_t *snake) {
    // If fruit was eaten, then new tile is created on the tail position and it shouldn't be moved now
    int size = snake->ate_fruit ? snake->size - 1 : snake->size;
    snake->ate_fruit = false;

    for (int i = 0; i < size; i++) {
        switch (snake->tiles[i].dir) {
            case UP:
                snake->tiles[i].y = (snake->tiles[i].y - 1 + TILES_IN_HEIGHT) % TILES_IN_HEIGHT;
                break;
            case DOWN:
                snake->tiles[i].y = (snake->tiles[i].y + 1) % TILES_IN_HEIGHT;
                break;
            case LEFT:
                snake->tiles[i].x = (snake->tiles[i].x - 1 + TILES_IN_WIDTH) % TILES_IN_WIDTH;
                break;
            case RIGHT:
                snake->tiles[i].x = (snake->tiles[i].x + 1) % TILES_IN_WIDTH;
                break;
        }
    }
}
