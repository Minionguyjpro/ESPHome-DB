#pragma once

void draw_header(Display &it) {
  it.print(5, 5, id(font20), id(lcd_yellow), "HELLO");

  if (id(system_status).state) {
    it.print(235, 5, id(font20), id(lcd_green),
             TextAlign::TOP_RIGHT, "Online");
  } else {
    it.print(235, 5, id(font20), id(lcd_red),
             TextAlign::TOP_RIGHT, "Offline");
  }
}
