#pragma once

#include "home_page.h"

void draw_page(esphome::display::Display &it, int page) {
  switch (page) {
    case 0:
      draw_home_page(it);
      break;

    default:
      draw_home_page(it);
      break;
  }
}
