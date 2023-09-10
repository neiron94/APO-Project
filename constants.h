#ifndef CONSTANTS_H

#define CONSTANTS_H


// PERIPHERALS
#define RGB_GREEN 0x0000ff00
#define RGB_RED 0x00ff0000
#define RGB_TIME 3
#define WRITE_CMD 0x2c


// SCREEN
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320


// IMAGES
#define GAME_BACK_IMG "/tmp/shvaiale/images/game_background.ppm"
#define MENU_BACK_IMG "/tmp/shvaiale/images/menu_background.ppm"
#define BUTTON_IMG "/tmp/shvaiale/images/button.ppm"
#define BUTTON_ACTIVE_IMG "/tmp/shvaiale/images/button_active.ppm"
#define FRUIT_IMG "/tmp/shvaiale/images/fruit.ppm"
#define SNAKE_1_HEAD_IMG "/tmp/shvaiale/images/snake1_head.ppm"
#define SNAKE_2_HEAD_IMG "/tmp/shvaiale/images/snake2_head.ppm"
#define SNAKE_1_TAIL_IMG "/tmp/shvaiale/images/snake1_tail.ppm"
#define SNAKE_2_TAIL_IMG "/tmp/shvaiale/images/snake2_tail.ppm"
#define SNAKE_1_BODY_IMG "/tmp/shvaiale/images/snake1_body.ppm"
#define SNAKE_2_BODY_IMG "/tmp/shvaiale/images/snake2_body.ppm"

#define BUTTON_W 177
#define BUTTON_H 87

#define TILE_SIZE 20


// MENU
#define MENU_SCALE 3

#define WORD_OFFSET_Y 20
#define WORD_OFFSET_X 35
// #define PLAY_OFFSET_X 35
// #define SPEED_OFFSET_X 25
// #define EXIT_OFFSET_X 35

#define WORD_COLOR 0x0
#define ARROW_COLOR 0xe9c3

#define BUTTON_X 150
#define BUTTON_1_Y 20
#define BUTTON_2_Y 117
#define BUTTON_3_Y 214

#define ARROW (char)0xaf


// GAME
#define PLAYER_START_X 5
#define PLAYER_START_Y 5
#define ENEMY_START_X 10
#define ENEMY_START_Y 10
#define FRUIT_START_X 5
#define FRUIT_START_Y 15

#define MAX_SIZE 25
#define START_SPEED 4
#define START_SIZE 3

#define TILES_IN_WIDTH 24
#define TILES_IN_HEIGHT 16


// DEFEAT
#define DEFEAT_SCALE 5
#define DEFEAT_WORD_X 120
#define DEFEAT_WORD_Y 120
#define DEFEAT_WORD_COLOR 0xf800


// VICTORY
#define VICTORY_SCALE 5
#define VICTORY_WORD_X 100
#define VICTORY_WORD_Y 110
#define VICTORY_WORD_COLOR 0xf800


#endif // CONSTANTS_H