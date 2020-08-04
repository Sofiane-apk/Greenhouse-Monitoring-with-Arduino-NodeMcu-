
##  Greenhouse Monitoring with Arduino  (Node Mcu v1.0 )


 ![version](https://img.shields.io/badge/version-1.0.0-blue.svg)  


![Product Gif](https://i.ibb.co/022dRK4/IOT-GH-bb.jpg)

  This script   reading   temperature and humidity of mini greenhouse and send it to firebase database real time   and  controlling  the pump, fan, and lamp . It has an automatic and manual pump mode :

1.  **Mode Automatic :** Soil sensor controle the pump according to the needs of the soil
2.  **Mode Manual :** We can control the pump from the website or the application
## Prerequisites
Installe this library
1. PubSubClient [https://github.com/knolleary/pubsubclient].

2. FirebaseArduino [https://github.com/FirebaseExtended/firebase-arduino]   **Note :** **Firebase certificate**  **fingerprint** has  changed. We can find this latter by typing our project URL appended by `/.json` in a browser and hit the lock icon to access certificate details. On the other side, in our FirebaseArduino library folder `firebase-arduino-master/src`, there is a file called `FirebaseHttpClient.h`. Inside it, there is a line where the fingerprint should be declared (hexadecimal digits by pairs). It has to match the one seen in the certificate details. That was no longer the case!

3. ESP8266WiFi [https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h]

4.  DHT-sensor-library  
[https://github.com/adafruit/DHT-sensor-library]


6. SoilMoisture [https://github.com/Apollon77/I2CSoilMoistureSensor]

7.  **Note : nodMcu restarting every time**   I Found that You Should have to downgrade the Esp Board Driver , i tried to downgrade to 2.3.0 and it worked perfectly fine no more exception

## Electric circuit

![Product Gif](https://i.ibb.co/4PNTpZP/IOT-GH-hardware-bb.jpg)

## Link
- [Firbase Hosting Dashboard Green House][https://github.com/Sofiane-apk/Firbase-Hosting--Dashboard-Green-House].
- [Dashboard Green House Application (android App)][https://github.com/Sofiane-apk/Dashboard-Green-House-Application].

-   Get started with IOT
[[https://medium.com/@o.lourme/our-iot-journey-through-esp8266-firebase-angular-and-plotly-js-part-1-a07db495ac5f](https://medium.com/@o.lourme/our-iot-journey-through-esp8266-firebase-angular-and-plotly-js-part-1-a07db495ac5f)]


