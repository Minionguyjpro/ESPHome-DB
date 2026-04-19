#pragma once

void draw_header(esphome::display::Display &it) {
  it.print(5, 5,
           id(font20),
           id(lcd_yellow),
           "HELLO");

  if (id(system_status).state) {
    it.print(235, 5,
             id(font20),
             id(lcd_green),
             esphome::display::TextAlign::TOP_RIGHT,
             "Online");
  } else {
    it.print(235, 5,
             id(font20),
             id(lcd_red),
             esphome::display::TextAlign::TOP_RIGHT,
             "Offline");
  }
}
