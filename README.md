# 12/24/21 Functional Design Link:
While I loved the concept of a wireless battery powered soil moisture sensor and performed much research on the topic in the accompanying documents, I have not been able to spare the time to revise and fix the flawed designs described within this repository. As such, I would like to redirect anyone searching to another team who has successfully designed and made a functional prototype available for open usage:

A LoRa enabled and battery powered soil moisture sensor has been designed by the people over at Makerfabs whose wireless transmission systems function correctly and has low energy consumption of around 7.1 uA. More information into the design and function of those functional products/designs can be found at either:
* [Lora Soil Moisture Sensor Project Github] (https://github.com/Makerfabs/Lora-Soil-Moisture-Sensor.git)
* [Makerfab Wiki Soil Moisture Sensor Page] (https://www.makerfabs.com/wiki/index.php?title=Lora_Soil_Moisture_Sensor.git)
---

# CloudGarden
This repository contains the work of a senior design project from the University of Kentucky to develop a **wireless battery powered outdoor soil moisture sensor**. 
---
- The *Hardware Design* section contains the Autodesk Eagle (created in 9.6.2) computer aided design (CAD) files and bill of materials (BOM) for a custom soil moisture sensor device PCB with functioning soil moisture and temperature sensing capability. 
- The *Software Design* section contains two methods of programming. One focused on decentralising the code and instantiating objects to seperately develop and integrate code piece by piece labeled *OOP*. The other, named *Functional* was focused on developing one central implementation without having to deal with many objects. Both are meant to be ran from the ArduinoIDE with the soil moisture sensor PCB being programmed as an Arduino Pro Mini with the libraries installed or added via the library manager.
- The *Integration Testing* section contains sections of code meant for testing separate sensing or communicaiton subsystems on the device while constructing

The **main difficulties** that disabled our ability to fully finish the project arose from a lack of understanding and prototyping of **Wireless LoRaWAN Communication** and **Serial Microcontroller Chip Connectivity**. Without a way of digitally recovering data from the device, we were unable to perform long-term testing to confirm sensing effectiveness and battery life. 

## Necessary Arduino Libraries
 * [RadioLib](https://github.com/jgromes/RadioLib.git)
 * [LowPower](https://github.com/LowPowerLab/LowPower.git)


