#include "periphs.h"


bool is_red_pressed(unsigned char *mem_base) {
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (r&0x4000000)!=0;
}

bool is_green_pressed(unsigned char *mem_base) {
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (r&0x2000000)!=0;
}

bool is_blue_pressed(unsigned char *mem_base) {
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (r&0x1000000)!=0;
}

void render_display(unsigned char *parlcd_mem_base, unsigned short *fb) {
    parlcd_write_cmd(parlcd_mem_base, WRITE_CMD);

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        parlcd_write_data(parlcd_mem_base, fb[i]);
}

void clean_display(unsigned char *parlcd_mem_base) {
    parlcd_write_cmd(parlcd_mem_base, WRITE_CMD);

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        parlcd_write_data(parlcd_mem_base, 0);
}

void light_rgb(unsigned char *mem_base, int time, uint32_t color) {
    struct timespec loop_delay = {.tv_sec = time, .tv_nsec = 0};

    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = color;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = color;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o) = 0;
    *(volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o) = 0;
}
