/*******************************************************************
  Project main function for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  start_app.c      - main file

  Shvaibovich Ales.
 *******************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "menu.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "structures.h"
#include "constants.h"
#include "images.h"
#include "periphs.h"


/**
 *  Map addresses, init display, load images, set start peripherals state.
 */
void init_all(periph_addrs_t *periph_addrs, images_t *images);

/**
 *  Map all necessary addresses.
 */
void map_addresses(periph_addrs_t *periph_addrs);

/** 
 *  Free alocated memory and clean screen and LED line before exit the pogram.
 */
void clean_all(periph_addrs_t *periph_addrs, unsigned short *fb);


int main(int argc, char *argv[]) {
    periph_addrs_t periph_addrs;
    images_t images;
    unsigned short *fb = (unsigned short*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * 2);

    init_all(&periph_addrs, &images);

    goto_menu(&periph_addrs, fb, &images);

    clean_all(&periph_addrs, fb);
}


void init_all(periph_addrs_t *periph_addrs, images_t *images) {
    map_addresses(periph_addrs);
    parlcd_hx8357_init(periph_addrs->parlcd_mem_base);
    load_images(images);
    *(volatile uint32_t*)(periph_addrs->mem_base + SPILED_REG_LED_LINE_o) = 0x0000ffff;
    *(volatile uint32_t*)(periph_addrs->mem_base + SPILED_REG_LED_RGB1_o) = 0;
    *(volatile uint32_t*)(periph_addrs->mem_base + SPILED_REG_LED_RGB2_o) = 0;
}


void map_addresses(periph_addrs_t *periph_addrs) {
    periph_addrs->mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (periph_addrs->mem_base == NULL) {
      fprintf(stderr, "Can't map mem_base address!\n");
      exit(1);
    }

  periph_addrs->parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (periph_addrs->parlcd_mem_base == NULL) {
      fprintf(stderr, "Can't map parlcd_mem_base address!\n");
      exit(1);
    }
}


void clean_all(periph_addrs_t *periph_addrs, unsigned short *fb) {
    clean_display(periph_addrs->parlcd_mem_base);
    *(volatile uint32_t*)(periph_addrs->mem_base + SPILED_REG_LED_LINE_o) = 0;
    free(fb);
}
