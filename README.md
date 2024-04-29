# Station Meteo

A multi-points, LoRa-based weather monitoring system.

Comprises:
- base station: display + Temp, humidity and CO2 sensors
- outdoor satellite: Temp, humidity and pressure sensors
- indoor satellite: Temp, humidity and CO2 sensors

# Notes

- Satellites to capture sensor values every 5 min and send to base over LoRa 433MHz
- Base updates screen every 5min
- battery-operated
- base, outdoor and indoor sats all have different firmwares.
- Display: 1 line per satellite, with freshness indicator (whether measure was received over last X min)

# TODO
- components selection
- circuit diagrams
- breakout builds
- code
- assembly
- shells

# BOM

Type | Name | Refs
-|-|-
Microcontroller | Heltec CubeCell HTCC-AB02A | https://heltec.org/project/htcc-ab02a/?attribute_pa_band=433mhz
Temp & humidity sensor
CO2 sensor | SCD40 | https://www.mouser.fr/ProductDetail/Adafruit/5187
Pressure sensor | LPS22 | https://www.adafruit.com/product/4633
screen
