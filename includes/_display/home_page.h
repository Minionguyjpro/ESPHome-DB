#pragma once

void draw_home_page(esphome::display::Display &it) {

  int y = (140 / 6) * 3 + 10;
  
  // Temperature (C)
  it.printf(5, y,
            &id(large),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °C",
            id(temperature).state);

  // Temperature (F)
  it.printf(5, y + 20,
            &id(medium),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °F",
            id(temperature).state * 9 / 5 + 32);
}
