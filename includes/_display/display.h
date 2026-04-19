#pragma once

#include "_display/background.h"
#include "_display/header.h"
#include "_display/home_page.h"

void draw_display(DisplayBuffer &it) {
  draw_background(it);
  draw_header(it);
  draw_home(it);
}
