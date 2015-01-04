//THIS WORK TOO
//
///* YourDuino Electronic Brick Test
//Temperature Sensor DS18B20
//- Connect cable to Arduino Digital I/O Pin 2
//terry@yourduino.com */
//
//#include <OneWire.h>
//#include <DallasTemperature.h>
//
//#define ONE_WIRE_BUS 4 /*-(Connect to Pin 2 )-*/
//
///*-----( Declare objects )-----*/
///* Set up a oneWire instance to communicate with any OneWire device*/
//OneWire ourWire(ONE_WIRE_BUS);
//
///* Tell Dallas Temperature Library to use oneWire Library */
//DallasTemperature sensors(&ourWire);
//
///*-----( Declare Variables )-----*/
//
//
//void setup()
//{
//    /*-(start serial port to see results )-*/
//    delay(1000);
//    Serial.begin(9600);
//    Serial.println("YourDuino.com: Electronic Brick Test Program");
//    Serial.println("Temperature Sensor DS18B20");
//    delay(1000);
//
//    /*-( Start up the DallasTemperature library )-*/
//    sensors.begin();
//}
//
//
//void loop()
//{
//    Serial.println();
//    Serial.print("Requesting temperature...");
//    sensors.requestTemperatures(); // Send the command to get temperatures
//    Serial.println("DONE");
//
//    Serial.print("Device 1 (index 0) = ");
//    Serial.print(sensors.getTempCByIndex(0));
//    Serial.println(" Degrees C");
//    Serial.print("Device 1 (index 0) = ");
//    Serial.print(sensors.getTempFByIndex(0));
//    Serial.println(" Degrees F");
//    delay(1000 * 4);
//}