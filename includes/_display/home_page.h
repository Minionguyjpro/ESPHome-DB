#pragma once

void draw_home_page(esphome::display::Display &it) {
  it.printf(240 / 2, (140 / 6) * 1 + 5,
            id(large),
            id(lcd_green),
            esphome::display::TextAlign::TOP_CENTER,
            "%.1f °C",
            id(temperature).state);

  it.printf(5, (140 / 6) * 3 + 10,
            id(medium),
            id(lcd_green),
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °F",
            id(temperature).state * 9 / 5 + 32);
}
