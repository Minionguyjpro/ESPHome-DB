# Tenstar Dynamic Display Layout

The `tenstar_elements` system lets you configure exactly which sensors and
text items appear on the Tenstar (ST7789V 240 × 135 px) display **without
editing any C++ header files**.  You register display elements from your
device YAML, and the renderer draws them every second.

---

## How it works

| File | Role |
|---|---|
| `includes/_display/tenstar_elements.h` | Defines the `TenstarElement` struct, the global registry, and the helper functions |
| `includes/_display/home_page.h` | Calls `tenstar_draw_elements()` when elements are registered; falls back to the original hard-coded layout otherwise |
| `includes/_display/display.h` | Entry point – includes all display headers including `tenstar_elements.h` |
| `common/nl/tenstar/ts-esp32-s3-dynamic.yaml` | Ready-to-use example YAML |

---

## Quick start

Use `ts-esp32-s3-dynamic.yaml` as your device package, or add an
`esphome.on_boot` lambda to your own YAML:

```yaml
packages:
  device:
    url: !secret repo_url
    files: [common/nl/tenstar/ts-esp32-s3-dynamic.yaml]
    refresh: 1h

substitutions:
  device_name: my-tenstar
  friendly_name: My Tenstar
  static_ip: 192.168.1.x
```

---

## Registering elements

All registrations happen inside an `esphome.on_boot` lambda at **priority 600**
(after sensors initialise, before the first display refresh).

```yaml
esphome:
  on_boot:
    priority: 600
    then:
      - lambda: |-
          // Static text
          tenstar_register_element(tenstar_make_text(
              5, 35,
              &id(font20), id(lcd_yellow),
              esphome::display::TextAlign::TOP_LEFT,
              "Weather Station"));

          // Float sensor – hidden automatically when the value is NaN
          tenstar_register_element(tenstar_make_float(
              5, 60,
              &id(medium), id(lcd_green),
              esphome::display::TextAlign::TOP_LEFT,
              "%.1f °C",
              []() { return id(temperature).state; }));

          // Conditional element – only shown while the device is online
          tenstar_register_element(tenstar_make_float(
              5, 100,
              &id(font20), id(lcd_blue),
              esphome::display::TextAlign::TOP_LEFT,
              "%.0f hPa",
              []() { return id(pressure).state; },
              []() { return id(system_status).state; }));
```

---

## Helper function reference

### `tenstar_make_float`

```cpp
TenstarElement tenstar_make_float(
    int x, int y,
    esphome::font::Font *font,
    esphome::Color color,
    esphome::display::TextAlign align,
    const char *format,
    std::function<float()> value,
    std::function<bool()> condition = {},   // optional
    bool skip_nan = true                    // optional
);
```

| Parameter | Description |
|---|---|
| `x`, `y` | Pixel coordinates of the text anchor |
| `font` | Font pointer, e.g. `&id(font20)` or `&id(medium)` |
| `color` | Foreground colour, e.g. `id(lcd_green)` |
| `align` | `TextAlign::TOP_LEFT`, `TOP_CENTER`, `TOP_RIGHT`, … |
| `format` | `printf`-style format string, e.g. `"%.1f °C"` |
| `value` | Lambda returning the sensor's `float` value |
| `condition` | *(optional)* Lambda returning `bool`; element hidden when `false` |
| `skip_nan` | *(optional, default `true`)* Hide element when `value()` is `NaN` |

### `tenstar_make_text`

```cpp
TenstarElement tenstar_make_text(
    int x, int y,
    esphome::font::Font *font,
    esphome::Color color,
    esphome::display::TextAlign align,
    const char *text,
    std::function<bool()> condition = {}    // optional
);
```

Same parameters as `tenstar_make_float` except `text` is a plain string and
there is no `value` or `skip_nan` argument.

### `tenstar_register_element`

```cpp
void tenstar_register_element(TenstarElement elem);
```

Appends an element to the registry.  Elements are drawn in registration order.

### `tenstar_clear_elements`

```cpp
void tenstar_clear_elements();
```

Removes all registered elements.  Useful when you want to rebuild the layout
at runtime (call `tenstar_clear_elements()` then re-register elements).

---

## Display coordinate system

The ST7789V panel on the Tenstar runs at **240 × 135 px** (rotation 90°):

```
(0,0) ─────────────────────── (239,0)
  │   Header bar  (y ≈ 0–25)        │
  │   Content area (y ≈ 25–135)     │
(0,134)─────────────────────(239,134)
```

The header bar (`draw_header`) is drawn at `y = 5` and is handled separately;
your registered elements should start at roughly `y = 35` to stay below it.

---

## Available fonts and colours

The Tenstar base YAML (`ts-esp32-s3.yaml`) pre-defines:

| ID | Description |
|---|---|
| `font20` / `roboto` | Roboto 20 px |
| `medium` | Roboto 35 px |
| `large` | Roboto 55 px |
| `lcd_red` | Red |
| `lcd_yellow` | Yellow |
| `lcd_green` | Green |
| `lcd_blue` | Blue |
| `lcd_gray` | Gray |

---

## Backward compatibility

Existing device YAMLs that **do not** call `tenstar_register_element` continue
to work unchanged.  `draw_home_page` falls back to the original hard-coded
temperature display when the registry is empty.
