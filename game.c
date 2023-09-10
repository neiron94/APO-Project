#include "game.h"


void goto_game(unsigned short *fb, periph_addrs_t *periph_addrs, images_t *images, int speed) {
    srand(time(NULL));
    snake_t player, enemy;
    init_snake(&player, PLAYER_START_X, PLAYER_START_Y);
    init_snake(&enemy, ENEMY_START_X, ENEMY_START_Y);
    fruit_t fruit = {.x = FRUIT_START_X, .y = FRUIT_START_Y};
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 120 * 1000 * 3000 / (speed + 1)}; // speed + 1, because speed can be 0

    while (true) {
        turn_head_player(periph_addrs->mem_base, &player);
        turn_head_enemy(&enemy, &fruit);
        
        eat_fruit(&player, &enemy, &fruit);

        grow(&player);
        grow(&enemy);

        move(&player);
        move(&enemy);

        change_tiles_dir(&player);
        change_tiles_dir(&enemy);

        draw_game(fb, periph_addrs->parlcd_mem_base, images, &fruit, &player, &enemy);
        
        if (is_colision(fb, periph_addrs, &player, &enemy)) break;  // go back to menu after colision
        
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
}


void draw_game(unsigned short *fb, unsigned char *parlcd_mem_base, images_t *images, fruit_t *fruit, snake_t *player, snake_t *enemy) {
    draw_background(fb, images->game_background);
    draw_fruit(fb, images->fruit, fruit);
    draw_snake(fb, images, enemy, false);
    draw_snake(fb, images, player, true);
    render_display(parlcd_mem_base, fb);
}


void defeat_action(unsigned short *fb, periph_addrs_t *periph_addrs) {
    print_word(fb, "DEFEAT", DEFEAT_WORD_X, DEFEAT_WORD_Y, DEFEAT_WORD_COLOR, DEFEAT_SCALE);
    render_display(periph_addrs->parlcd_mem_base, fb);
    light_rgb(periph_addrs->mem_base, RGB_TIME, RGB_RED);
}


void victory_action(unsigned short *fb, periph_addrs_t *periph_addrs) {
    print_word(fb, "VICTORY", VICTORY_WORD_X, VICTORY_WORD_Y, VICTORY_WORD_COLOR, VICTORY_SCALE);
    render_display(periph_addrs->parlcd_mem_base, fb);
    light_rgb(periph_addrs->mem_base, RGB_TIME, RGB_GREEN);
}
