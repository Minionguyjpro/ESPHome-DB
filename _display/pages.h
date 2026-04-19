#pragma once

void draw_home(DisplayBuffer &it) {
  it.printf(120, 60, id(large), "%.1f°C", id(temperature).state);
}

void draw_page(DisplayBuffer &it, int page) {
  switch (page) {
    case 0: draw_home(it); break;
  }
}
