#pragma once
/**
 * Tenstar Dynamic Display Element System
 * =======================================
 * Provides a data-driven way to render sensors and text on the Tenstar
 * (ST7789V, 240 x 135 px) display without hard-coding every item inside the
 * display lambda.
 *
 * ── Quick start ────────────────────────────────────────────────────────────
 *
 * In your device YAML add an on_boot action that registers the elements you
 * want.  All helper functions are available because this header is included
 * transitively through display.h.
 *
 *   esphome:
 *     on_boot:
 *       priority: 600
 *       then:
 *         - lambda: |-
 *             // Static title
 *             tenstar_register_element(tenstar_make_text(
 *                 5, 35, &id(font20), id(lcd_yellow),
 *                 esphome::display::TextAlign::TOP_LEFT,
 *                 "My Device"));
 *
 *             // Float sensor (hidden when the reading is NaN)
 *             tenstar_register_element(tenstar_make_float(
 *                 5, 60, &id(medium), id(lcd_green),
 *                 esphome::display::TextAlign::TOP_LEFT,
 *                 "%.1f °C",
 *                 []() { return id(temperature).state; }));
 *
 *             // Conditional element – only shown when online
 *             tenstar_register_element(tenstar_make_float(
 *                 5, 100, &id(font20), id(lcd_blue),
 *                 esphome::display::TextAlign::TOP_LEFT,
 *                 "%.0f hPa",
 *                 []() { return id(pressure).state; },
 *                 []() { return id(system_status).state; }));
 *
 * See docs/tenstar-dynamic-display.md for the full reference.
 */

#include <cmath>
#include <functional>
#include <vector>

/**
 * One renderable item on the Tenstar display.
 *
 * Fields
 * ------
 * x, y          Pixel coordinates of the element's anchor point.
 * font          Pointer to an ESPHome font object, e.g. &id(font20).
 * color         Foreground colour, e.g. id(lcd_green).
 * align         TextAlign anchor for (x, y).
 * format        printf-style format string.  For static text this is the
 *               literal string to print; float_value should be left empty.
 * float_value   Lambda returning the float to embed in the format string.
 *               Leave empty ({}) for static text elements.
 * condition     Optional visibility guard.  The element is skipped when this
 *               returns false.  Leave empty ({}) to always render.
 * skip_if_nan   When true (default) the element is skipped if float_value()
 *               returns NaN.
 */
struct TenstarElement {
  int x{0};
  int y{0};
  esphome::font::Font *font{nullptr};
  esphome::Color color{esphome::Color::WHITE};
  esphome::display::TextAlign align{esphome::display::TextAlign::TOP_LEFT};
  const char *format{""};
  std::function<float()> float_value{};
  std::function<bool()> condition{};
  bool skip_if_nan{true};
};

// Ordered list of elements rendered on every display refresh.
// Populated at boot via tenstar_register_element(); cleared with
// tenstar_clear_elements() if a runtime layout change is needed.
//
// ESPHome custom headers are compiled into a single translation unit, so
// there is no static-initialisation order issue with this global.
inline std::vector<TenstarElement> tenstar_elements;

/**
 * Append one element to the registry.
 * Call this from an esphome.on_boot lambda (priority ≥ 600).
 */
inline void tenstar_register_element(TenstarElement elem) {
  tenstar_elements.push_back(std::move(elem));
}

/** Remove all registered elements (useful when rebuilding the layout at runtime). */
inline void tenstar_clear_elements() {
  tenstar_elements.clear();
}

/**
 * Render every registered element onto the display.
 * Called automatically by draw_home_page() when elements have been registered.
 * You can also call it directly from the display lambda if you bypass the
 * default draw_home_page() function.
 */
inline void tenstar_draw_elements(esphome::display::Display &it) {
  for (const auto &elem : tenstar_elements) {
    if (elem.font == nullptr) continue;
    if (elem.condition && !elem.condition()) continue;

    if (elem.float_value) {
      float val = elem.float_value();
      if (elem.skip_if_nan && std::isnan(val)) continue;
      it.printf(elem.x, elem.y,
                elem.font,
                elem.color,
                esphome::display::COLOR_OFF,
                elem.align,
                elem.format,
                val);
    } else {
      it.print(elem.x, elem.y,
               elem.font,
               elem.color,
               elem.align,
               elem.format);
    }
  }
}

// ── Convenience constructors ──────────────────────────────────────────────

/**
 * Build a float-sensor element.
 *
 * @param x, y       Pixel coordinates.
 * @param font       ESPHome font pointer (e.g. &id(medium)).
 * @param color      Foreground colour (e.g. id(lcd_green)).
 * @param align      Text alignment anchor.
 * @param format     printf format string (e.g. "%.1f °C").
 * @param value      Lambda returning the float sensor value.
 * @param condition  Optional visibility guard; pass {} to always show.
 * @param skip_nan   Skip when value() is NaN (default true).
 */
inline TenstarElement tenstar_make_float(
    int x, int y,
    esphome::font::Font *font,
    esphome::Color color,
    esphome::display::TextAlign align,
    const char *format,
    std::function<float()> value,
    std::function<bool()> condition = {},
    bool skip_nan = true) {
  TenstarElement elem;
  elem.x = x;
  elem.y = y;
  elem.font = font;
  elem.color = color;
  elem.align = align;
  elem.format = format;
  elem.float_value = std::move(value);
  elem.condition = std::move(condition);
  elem.skip_if_nan = skip_nan;
  return elem;
}

/**
 * Build a static-text element.
 *
 * @param x, y       Pixel coordinates.
 * @param font       ESPHome font pointer (e.g. &id(font20)).
 * @param color      Foreground colour (e.g. id(lcd_yellow)).
 * @param align      Text alignment anchor.
 * @param text       The string to display.
 * @param condition  Optional visibility guard; pass {} to always show.
 */
inline TenstarElement tenstar_make_text(
    int x, int y,
    esphome::font::Font *font,
    esphome::Color color,
    esphome::display::TextAlign align,
    const char *text,
    std::function<bool()> condition = {}) {
  TenstarElement elem;
  elem.x = x;
  elem.y = y;
  elem.font = font;
  elem.color = color;
  elem.align = align;
  elem.format = text;
  elem.condition = std::move(condition);
  return elem;
}
