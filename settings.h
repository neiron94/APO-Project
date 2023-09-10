#ifndef SPEED_SETTING_H

#define SPEED_SETTING_H

#include <stdint.h>
#include <stdbool.h>

#include "mzapo_regs.h"
#include "constants.h"


/**
 *  Start "settings mode", where speed can be chosen.
 */
int goto_settings(unsigned char *mem_base);

#endif //SPEED_SETTING_H