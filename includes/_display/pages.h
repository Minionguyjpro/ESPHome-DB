#pragma once

void draw_home_page(esphome::display::Display &it) {
  it.printf(120, 60, id(large), "%.1f°C", id(temperature).state);
}

void draw_page(esphome::display::Display &it, int page) {
  switch (page) {
    case 0:
      draw_home_page(it);
      break;
  }
}
