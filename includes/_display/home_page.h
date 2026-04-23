#pragma once

// tenstar_elements.h is included via display.h before this header, but pull
// it in explicitly so home_page.h is self-contained when included on its own.
#include "tenstar_elements.h"

void draw_home_page(esphome::display::Display &it) {

  // ── Dynamic layout ───────────────────────────────────────────────────────
  // When elements have been registered at boot (via tenstar_register_element),
  // render them and skip the hard-coded fallback below.
  if (!tenstar_elements.empty()) {
    tenstar_draw_elements(it);
    return;
  }

  // ── Hard-coded fallback (backward compatibility) ─────────────────────────
  // Used when no elements have been registered, so that existing device YAMLs
  // that do NOT call tenstar_register_element continue to work unchanged.

  int x = 5;
  int y = (140 / 6) * 3 + 10;
  
  // Temperature (C)
  it.printf(x, y,
            &id(medium),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °C",
            id(temperature).state);

  // Temperature (F)
  it.printf(x, y + 20,
            &id(medium),
            id(lcd_green),
            esphome::display::COLOR_OFF,
            esphome::display::TextAlign::TOP_LEFT,
            "%.1f °F",
            id(temperature).state * 9 / 5 + 32);
}
