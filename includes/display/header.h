#pragma once

void draw_header(DisplayBuffer &it) {
  it.print(5, 5, id(font20), "HELLO");

  if (id(system_status).state) {
    it.print(235, 5, id(font20), TextAlign::TOP_RIGHT, "Online");
  } else {
    it.print(235, 5, id(font20), TextAlign::TOP_RIGHT, "Offline");
  }
}
