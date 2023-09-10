#include "menu.h"


void goto_menu(periph_addrs_t *periph_addrs, unsigned short *fb, images_t *images) {
    int chosen_option = PLAY, snake_speed = START_SPEED;
    bool is_exit = false;
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 120 * 1000 * 1000};
  
    while (true) {
      draw_menu_panel(fb, periph_addrs->parlcd_mem_base, images, chosen_option, NONE);
      chosen_option = update_choose(chosen_option, periph_addrs->mem_base);

      if (is_red_pressed(periph_addrs->mem_base)) {
        switch(chosen_option) {
          case PLAY:
            draw_menu_panel(fb, periph_addrs->parlcd_mem_base, images, chosen_option, PLAY);
            goto_game(fb, periph_addrs, images, snake_speed);
            break;
          case SPEED:
            draw_menu_panel(fb, periph_addrs->parlcd_mem_base, images, chosen_option, SPEED);
            snake_speed = goto_settings(periph_addrs->mem_base);
            break;
          case EXIT:
            draw_menu_panel(fb, periph_addrs->parlcd_mem_base, images, chosen_option, EXIT);
            is_exit = true;
            break;
        }
      }

      if (is_exit)  break;  // go back to start_app function, where program will be finished

      clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
}


int update_choose(int current_option, unsigned char *mem_base) {
    if (is_blue_pressed(mem_base))
      current_option = (current_option + 1) % OPTIONS_COUNT;
    else if (is_green_pressed(mem_base))
      current_option = (current_option - 1 + OPTIONS_COUNT) % OPTIONS_COUNT;
    
    return current_option;
}


void draw_menu_panel(unsigned short *fb, unsigned char *parlcd_mem_base, images_t *images, int chosen_option, int active_button) {
    draw_background(fb, images->menu_background);
      
    if (active_button == PLAY)  draw_button(fb, images->button_active, BUTTON_X, BUTTON_1_Y, "Play");
    else                        draw_button(fb, images->button, BUTTON_X, BUTTON_1_Y, "Play");

    if (active_button == SPEED) draw_button(fb, images->button_active, BUTTON_X, BUTTON_2_Y, "Speed");
    else                        draw_button(fb, images->button, BUTTON_X, BUTTON_2_Y, "Speed");

    if (active_button == EXIT)  draw_button(fb, images->button_active, BUTTON_X, BUTTON_3_Y, "Exit");
    else                        draw_button(fb, images->button, BUTTON_X, BUTTON_3_Y, "Exit");

    print_arrow(fb, chosen_option, MENU_SCALE);

    render_display(parlcd_mem_base, fb);
}
