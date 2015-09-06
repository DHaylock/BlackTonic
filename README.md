Black Tonic
===

#### Introduction

This is a collaboration between Watershed and The Other Way Works, to create a card table which plays sound files when cards are placed on the table. The system uses OSC to communicate between oF and QLab.
### Components
The system is comprised of the following components:

##### Hardware
* 1 x Mac Mini
* 1 x Arduino Mega
* 1 x [RFID USB Reader](https://www.coolcomponents.co.uk/rfid-usb-reader.html?gclid=Cj0KEQjwyK-vBRCp4cymxermx-EBEiQATOQgh4K8bH5pXxSo0pucvdKxIaLxiuDYaz_oSJ8dV2An9VUaAgcc8P8HAQ)
* 1 x [RFID Reader](https://www.coolcomponents.co.uk/rfid-reader-id-20-125-khz.html)
* 12 x [LDR Sensors](http://oomlout.co.uk/collections/extra-pieces/products/photo-resistor-x5)

###### Software
* openFrameworks Application
* QLab

#### Dependancies

The code has the following dependancies:
* [ofxSimpleTimer](https://github.com/DHaylock/ofxSimpleTimer) (Forked and Altered)
* [ofxJSON](https://github.com/jefftimesten/ofxJSON)

#### How to alter
There is a json file in the data folder of the application.
The following Variables are alterable:
* ```arduinoname```
* ```rfiddevicename```
* ```osc: hostname, port```
* ```delaytimer``` which is responsible for the triggering time
* ```threshold``` which is the approximate dark level for the trigger
* ```rfidtags``` tag one and two are the two triggers

Simply alter the variables in there an relaunch the application.

If the Arduino does not respond:
* Open terminal
* Enter the following code
* ``` ls -l /dev/tty* ```
* You should see a similar response
* ``` crw-rw-rw-  1 root   wheel    2,   0  6 Sep 12:15 /dev/tty ```
* Arduino's generally have the address of ```/dev/tty.usbmodem*```
* Check the Config folder and check whether the addresses match.

Likewise if the RFID Reader isn't responding copy the address into the config file

#### UI
![alt text](BlackTonicUI.png "UI")
