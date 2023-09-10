#include "settings.h"


int goto_settings(unsigned char *mem_base) {

    int speed = START_SPEED, value = 0, prev_value = 0;

    while (true) {
        int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

        value = ((r >> 16) & 0xff) / 4;
        // Turn right
        if ((value > prev_value || prev_value - value > 20) && speed < 8)
            speed++;
        // Turn left
        if ((value < prev_value || value - prev_value > 20) && speed > 0)
            speed--;

        prev_value = value;


        value = 0xffffffff >> (32 - speed * 4);
        *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = value;

        if ((r & 0x2000000) != 0)
            return speed;
    }
}
