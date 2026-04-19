#pragma once

void draw_home_page(esphome::display::Display &it) {

  // Temperature (C)
  it.printf(120, 60,
            static_cast<esphome::display::BaseFont *>(id(large)),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_CENTER,
            "%.1f °C",
            id(temperature).state);

  // Temperature (F)
  it.printf(5, (140 / 6) * 3 + 10,
            istatic_cast<esphome::display::BaseFont *>(id(medium))
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °F",
            id(temperature).state * 9 / 5 + 32);
}
