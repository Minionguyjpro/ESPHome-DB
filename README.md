# ESPHome-DB
Database with config files for my own ESPHome setup.
## Usage
To use in your own project, only specify something like the following inside your device's YAML:
```yaml
packages:
  device:
    url: !secret repo_url
    files: [common/nl/lsc/smart_plug_2578685.yaml, common/nl/wireguard.yaml]
    refresh: 1h
```
