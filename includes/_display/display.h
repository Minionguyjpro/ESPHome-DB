#pragma once

#include "background.h"
#include "header.h"
#include "home_page.h"

void draw_display(DisplayBuffer &it) {
  draw_background(it);
  draw_header(it);
  draw_home(it);
}
