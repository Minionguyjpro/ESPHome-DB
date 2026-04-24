# ESPHome-DB
Database with config files for my own ESPHome setup. Feel free to reuse or make contributions.
The goal of this project is to make my ESPHome ecosystem as modular as possible, reusing common sensors as much as possible to make every device in your home equally capable!
## Usage
To use in your own project, only specify something like the following inside your device's YAML:
```yaml
packages:
  device:
    url: !secret repo_url
    files: [common/nl/lsc/smart_plug_2578685.yaml]
    refresh: 1h

substitutions:
  device_name: aquariumlamp
  friendly_name: Aquariumlamp
  static_ip: 192.168.1.105
  wifi_ssid: !secret wifi_ssid_lan
  wifi_password: !secret wifi_password_lan
  gateway_ip: !secret gateway_ip_lan
  subnet_mask: !secret subnet_mask
```

## Global IDs
| **ID**           | **Type**     | **Description**                  | **Example Usage**             |
|------------------|--------------|----------------------------------|-------------------------------|
| ``local_time``   | Time         | Current local time (RTC/SNTP)    | ``id(local_time).now().hour`` |
| ``ha_connected`` | BinarySensor | State of HA connection (on/off)  |                               |
|                  |              |                                  |                               |
