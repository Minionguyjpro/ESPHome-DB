#pragma once

void draw_home_page(esphome::display::Display &it) {

  int x = 5;
  int y = (140 / 6) * 3 + 10;
  
  // Temperature (C)
  it.printf(x, y,
            &id(medium),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °C",
            id(temperature).state);

  // Temperature (F)
  it.printf(x, y + 20,
            &id(medium),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °F",
            id(temperature).state * 9 / 5 + 32);
}
