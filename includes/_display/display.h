#pragma once

#include "background.h"
#include "header.h"
#include "home_page.h"
#include "pages.h"

void draw_display(esphome::display::Display &it) {
  draw_background(it);
  draw_header(it);
  draw_home_page(it);
}
