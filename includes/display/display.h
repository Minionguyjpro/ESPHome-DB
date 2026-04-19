#pragma once

#include "header.h"
#include "pages.h"

void draw_display(DisplayBuffer &it) {
  draw_header(it);
  draw_page(it, id(current_page));
}
