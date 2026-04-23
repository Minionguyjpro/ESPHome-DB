#pragma once

void draw_home_page(esphome::display::Display &it) {
  // Display is 240 x 135 px (rotation 90°).
  // Header bar occupies y=0..25; content area starts at y=28.
  int x = 5;

  // Temperature in °C
  it.printf(x, 28,
            &id(medium),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °C",
            id(temperature).state);

  // Temperature in °F
  it.printf(x, 68,
            &id(font20),
            id(lcd_gray),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °F",
            id(temperature).state * 9.0f / 5.0f + 32.0f);

  // Atmospheric pressure
  it.printf(x, 92,
            &id(font20),
            id(lcd_blue),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f hPa",
            id(pressure).state);

  // Internal chip temperature
  it.printf(x, 114,
            &id(roboto),
            id(lcd_gray),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "Chip: %.0f °C",
            id(internal_temperature).state);
}
