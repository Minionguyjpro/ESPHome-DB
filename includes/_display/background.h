#pragma once

void draw_background(Display &it) {
  it.rectangle(0, 0, it.get_width(), it.get_height(), id(lcd_blue));
  it.rectangle(0, 25, it.get_width(), it.get_height(), id(lcd_blue));
}
