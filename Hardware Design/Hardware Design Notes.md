# Hardware Design 
The following are notes from the Autodesk Eagle 9.6.2 created PCB files and physical construction of our wireless soil moisture sensor devices.
---

## Issues with version 5.0
While undergoing hardware integration of our final prototype (5.0), we had several issues that we were unable to resolve including:

- The RFM69HCW is inferior compared to the RFM95HCW by our wireless developer due to a lack of a full FSK Modem.
- The antenna we selected did not fit the port or footprint we used for the associated connector on our PCB.
- The battery monitoring circuit was never implemented and deemed unnecessary due to existing methods of internal bandgap voltage reference supply voltage measurement.
- The FTDI to USB circuit as we ported it from the Beefy FTDI to USB circuit did not function as intended. 
- Programming the microcontroller chip through the ICSP connection is not possible with the RFM69HCW system attached due to programming interference on the bus. This could be resolved by using a solder jumper to connect to the data lines or power the RFM69HCW device when desired.

The final two issues could both be solved by simplifying the design by using a small power-efficient microcontroller with built-in USB or even built-in LoRa such as the [Seeeduino Xiao](https://www.seeedstudio.com/Seeeduino-XIAO-Pre-Soldered-p-4747.html). 

## Licensing and Sources
The circuits used within our custom PCB's hardware design were sourced from a variety of webpages/companies distributed via open source licenses with ShareAlike and Attribution conditions. 

- The setup used for the ATMEGA328P chip was adapted from the schematic for the Arduino Pro Mini with the schematic available [on Arduino's website](https://www.arduino.cc/en/pmwiki.php?n=Main/ArduinoBoardProMini). This system was originally ddesigned by Team Arduino and modified by Spark Fun Electronics. It's schematic is released under the [Creative Commons Attribution Share-Alike 3.0 License](http://creativecommons.org/licenses/by-sa/3.0).
- The Capacitive Soil Moisture sensing circuit was adapted from the version showcased in Placidi, P.; Gasperini, L.; Grassi, A.; Cecconi, M.; Scorzoni, A. [Characterization of Low-Cost Capacitive Soil Moisture Sensors for IoT Networks](https://www.mdpi.com/1424-8220/20/12/3585). Sensors 2020, 20, 3585. https://doi.org/10.3390/s20123585.
- The FTDI to USB circuit was adapted from the schematics freely available for the [SparkFun Beefy 3 - FTDI Basic Breakout](https://www.sparkfun.com/products/13746) designed by Brent Wilkins from SparkFun and released under the [Creative Commons Attribution Share-Alike 4.0 License](https://creativecommons.org/licenses/by-sa/4.0/).
- The RFM69HCW application circuit was derived from the application circuits available in the datasheet and accompanying auxillary documentation available on [Digikey](https://www.digikey.com/en/products/detail/sparkfun-electronics/COM-13909/6023504).
- The MAX17201 battery monitor application circuit was also derived from the application circuits available in the datasheet and accompanyin auxillary documentation available on [Digikey](https://www.digikey.com/en/products/detail/maxim-integrated/MAX17201G-T/5880644).