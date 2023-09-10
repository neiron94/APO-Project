#include "print.h"


void print_arrow(unsigned short *fb, int option, int scale) {
    int x = BUTTON_X - char_width(ARROW) * scale;
    int y = 0;

    switch (option) {
        case PLAY:
          y = BUTTON_1_Y + WORD_OFFSET_Y;
          break;
        case SPEED:
          y = BUTTON_2_Y + WORD_OFFSET_Y;
          break;
        case EXIT:
          y = BUTTON_3_Y + WORD_OFFSET_Y;
          break;
    }

    print_char(fb, x, y, ARROW, ARROW_COLOR, scale);
}


 
void print_word(unsigned short *fb, char *word, int x, int y, unsigned short color, int scale) {
    int i = 0;
    while (word[i] != '\0') {
        print_char(fb, x + i * char_width(word[i]) * scale, y, word[i], color, scale);
        i++;
    }
}

void draw_pixel(unsigned short *fb, int x, int y, unsigned short color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        fb[x + SCREEN_WIDTH * y] = color;
}
 
void draw_pixel_big(unsigned short *fb, int x, int y, unsigned short color, int scale) {
    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
            draw_pixel(fb, x + i, y + j, color);
}
 
int char_width(int ch) {
  font_descriptor_t *fdes = &font_rom8x16;
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch - fdes->firstchar];
  }
  return width;
}
 
void print_char(unsigned short *fb, int x, int y, char ch, unsigned short color, int scale) {
  font_descriptor_t *fdes = &font_rom8x16;
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth + 15) / 16;
      ptr = &fdes->bits[(ch-fdes->firstchar) * bw * fdes->height];
    }
    
    for (int i = 0; i < fdes->height; i++) {
      font_bits_t val = *ptr;
      for (int j = 0; j < w; j++) {
        if ((val & 0x8000)!=0) {
          draw_pixel_big(fb, x+scale*j, y+scale*i, color, scale);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}
