#pragma once

#include "background.h"
#include "header.h"
#include "home_page.h"

void draw_display(Display &it) {
  draw_background(it);
  draw_header(it);
  draw_home(it);
}
