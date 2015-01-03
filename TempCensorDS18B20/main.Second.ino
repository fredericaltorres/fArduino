///*
//Controlling the tempetature sensor DS18B20 with the Arduino
//http://www.hobbytronics.co.uk/ds18b20-arduino
//http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
//Ref http://arduino.cc/en/Reference/HomePage
//*/
//
//#include "OneWire.h"
//#include "fArduino.h"
//#include "DS18B20TemperatureSensor.h"
//
//#define SPEAKER_PIN 9
//int musicSequenceIntro[] = {
//    NOTE_C4, 8,
//    NOTE_C4, 8,
//    NOTE_G3, 8,
//    NOTE_G3, 8,
//    NOTE_A3, 4,
//    NOTE_G3, 4,
//    NOTE_SILENCE, 4,
//    NOTE_B3, 4,
//    NOTE_C4, 8,
//    NOTE_C3, 8,
//    NOTE_C2, 8,
//    NOTE_C1, 4,
//};
//
//int musicSequenceIntroa[] = {
//    NOTE_C5, 28,
//    NOTE_C5, 20,
//    NOTE_C5, 28,
//    NOTE_C5, 20,
//    NOTE_C5, 28,
//
//    NOTE_C4, 16,
//    NOTE_C4, 16,
//    NOTE_C4, 8,
//    NOTE_C4, 8,
//    NOTE_C3, 4,
//    NOTE_C3, 4,
//    NOTE_C2, 2,
//    //NOTE_C1, 2,
//};
//
//SpeakerManager _speakerManager(SPEAKER_PIN);
//
//#define ONE_WIRE_BUS 2
//
//OneWire                  _oneWire(ONE_WIRE_BUS);
//DS18B20TemperatureSensor _DS18B20(&_oneWire);
//TimeOut                  _oneSecondTimeOut(1000);
//
//void setup() {
//
//    Board.InitializeComputerCommunication(9600, "Initializing...");
//    Board.TraceHeader("Temperature Sensor DS18B20");
//    Board.Trace(StringFormat.Format("Sensor ID:%d, Name:%s",
//        _DS18B20.GetSensorId(), _DS18B20.GetSensorName()));
//
//    Board.Trace(StringFormat.Format("Sensor Unique Ids:%s", _DS18B20.GetSensorUniqueIdsOn1Wire().c_str()));
//    Board.Trace("Ready...");
//
//    _speakerManager.PlaySequence(ArraySize(musicSequenceIntro), musicSequenceIntro);
//    Board.Delay(1000);
//    //_speakerManager.PlaySequence(ArraySize(musicSequenceIntro), musicSequenceIntro, SPEAKERMANAGER_PLAY_SEQUENCE_NORMAL, SPEAKERMANAGER_PLAY_SEQUENCE_REVERSE);
//
//    Board.SetPinMode(SPEAKER_PIN, OUTPUT);
//}
//
//void loop() {
//
//    /*   for (int i = 0; i<64; i += 3) {
//    analogWrite(SPEAKER_PIN, i);
//    delay(5);
//    }*/
//
//    static double previousCelsius;
//
//    if (_oneSecondTimeOut.IsTimeOut()) {
//
//        double celsius = _DS18B20.GetTemperature();
//
//        if (previousCelsius != celsius || _oneSecondTimeOut.EveryCalls(10)) {
//
//            double fahrenheit = _DS18B20.CelsiusToFahrenheit(celsius);
//            Board.Trace(StringFormat.Format("[%s, mem:%d] %fC - %fF", StringFormat.GetTime(), Board.GetFreeMemory(), celsius, fahrenheit));
//            previousCelsius = celsius;
//        }
//    }
//}
