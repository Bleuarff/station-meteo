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
- circuit diagrams
- breakout builds
- code
- assembly
- shells
- PCB

# BOM

Type | Name | Refs
-|-|-
Microcontroller | Heltec CubeCell HTCC-AB02A | https://heltec.org/project/htcc-ab02a/?attribute_pa_band=433mhz
Temp & humidity sensor | AHT20 | https://www.adafruit.com/product/4566
CO2 sensor | SCD40 | https://www.adafruit.com/product/5187
Pressure sensor | LPS22HB | https://www.adafruit.com/product/4633
screen | eInk 2.13" monochrome 250x122 (SSD1680) | https://www.adafruit.com/product/4197

# Parts documentation

Name | Url
-|-
AHT20 | https://asairsensors.com/wp-content/uploads/2021/09/Data-Sheet-AHT20-Humidity-and-Temperature-Sensor-ASAIR-V1.0.03.pdf
LPS22HB | https://www.mouser.fr/pdfdocs/enDM00140895.pdf
Screen | https://learn.adafruit.com/adafruit-2-13-eink-display-breakouts-and-featherwing
CubeCell | https://resource.heltec.cn/download/CubeCell/HTCC-AB02A/HTCC-AB02A_PinoutDiagram.pdf <br> https://docs.heltec.org/en/node/asr650x/htcc_ab02/index.html <br>

# Setup

- Create a symlink for each library:
````bash
ln -s ~/dev/station-meteo/sketches/libraries/aht20 ~/dev/station-meteo/sketches/libraries/lps22 ~/Arduino/libraries/
````