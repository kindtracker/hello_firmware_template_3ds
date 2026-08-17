#include "ui.h"
#include "i2c.h"
#include "cache.h"
#include "qff.h"
#include "utils.h"

uint8_t *top_screen, *bottom_screen;

void main(int argc, char** argv) {
  if (argc >= 2) {
    uint8_t **fb = (uint8_t **)(void *)argv[1];
    top_screen = fb[0];
    bottom_screen = fb[2];
  } else {
    top_screen = (uint8_t *)(*(uint32_t *)0x23FFFE00);
    bottom_screen = (uint8_t *)(*(uint32_t *)0x23FFFE08);
  }

  ClearScreenF(true, true, COLOR_STD_BG);
  
  while (true) {
    DrawStringF(bottom_screen, 4, 4, COLOR_STD_FONT, COLOR_STD_BG, "Hello, 3DS!\n");
    if (!(system_shellstate() & 2)) {
      break;
    }
  }

  fs_deinit();
  ClearScreenF(true, true, COLOR_STD_BG);
  
  system_poweroff();
}
