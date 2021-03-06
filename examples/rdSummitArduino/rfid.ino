///*
//* ----------------------------------------------------------------------------
//* This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
//* for further details and other examples.
//*
//* NOTE: The library file MFRC522.h has a lot of useful info. Please read it.
//*
//* Released into the public domain.
//* ----------------------------------------------------------------------------
//* Example sketch/program showing how to read data from a PICC (that is: a RFID
//* Tag or Card) using a MFRC522 based RFID Reader on the Arduino SPI interface.
//*
//* When the Arduino and the MFRC522 module are connected (see the pin layout
//* below), load this sketch into Arduino IDE then verify/compile and upload it.
//* To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M).
//* When you present a PICC (that is: a RFID Tag or Card) at reading distance
//* of the MFRC522 Reader/PCD, the serial output will show the ID/UID, type and
//* any data blocks it can read. Note: you may see "Timeout in communication"
//* messages when removing the PICC from reading distance too early.
//*
//* If your reader supports it, this sketch/program will read all the PICCs
//* presented (that is: multiple tag reading). So if you stack two or more
//* PICCs on top of each other and present them to the reader, it will first
//* output all details of the first and then the next PICC. Note that this
//* may take some time as all data blocks are dumped, so keep the PICCs at
//* reading distance until complete.
//*
//* Typical pin layout used:
//* -----------------------------------------------------------------------------------------
//*             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
//*             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
//* Signal      Pin          Pin           Pin       Pin        Pin              Pin
//* -----------------------------------------------------------------------------------------
//* RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
//* SPI SS      SDA(SS)      10            53        D10        10               10
//* SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
//* SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
//* SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
//*/
//
//#include <SPI.h>
//#include <MFRC522.h>
//
//#define RST_PIN		9		// 
//#define SS_PIN		10		//
//
//MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance
//
//void setup() {
//
//    Serial.begin(9600);		// Initialize serial communications with the PC
//    while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
//    SPI.begin();			// Init SPI bus
//    mfrc522.PCD_Init();		// Init MFRC522
//
//    delay(2000);
//
//    ShowReaderDetails();	// Show details of PCD - MFRC522 Card Reader details
//    Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
//}
//
//#define Flush Serial.flush(); delay(10);
//
//void loop() {
//    // Look for new cards
//    if (!mfrc522.PICC_IsNewCardPresent()) {
//        return;
//    }
//
//
//    // Select one of the cards
//    if (!mfrc522.PICC_ReadCardSerial()) {
//        return;
//    }
//
//    Serial.print("mfrc522.uid.size:");
//    Serial.println(mfrc522.uid.size);
//    Flush;
//
//    Serial.print("PICC_GetUidAsLong:");
//    Serial.println(mfrc522.PICC_GetUidAsLong());
//    Flush;
//
//    byte type = mfrc522.PICC_GetType(mfrc522.uid.sak);
//    Serial.println(mfrc522.PICC_GetTypeName(type));
//    Flush;
//
//    delay(1000 * 2);
//
//    // Dump debug info about the card; PICC_HaltA() is automatically called
//    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
//}
//
//void ShowReaderDetails() {
//    // Get the MFRC522 software version
//    byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
//    Serial.print(F("MFRC522 Software Version: 0x")); Serial.flush(); delay(10);
//    Serial.print(v, HEX); Serial.flush(); delay(10);
//    if (v == 0x91)
//        Serial.print(F(" = v1.0"));
//    else if (v == 0x92)
//        Serial.print(F(" = v2.0"));
//    else
//        Serial.print(F(" (unknown)"));
//    Serial.println("");
//
//    Serial.flush(); delay(10);
//
//    // When 0x00 or 0xFF is returned, communication probably failed
//    if ((v == 0x00) || (v == 0xFF)) {
//        Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
//    }
//
//    Serial.flush(); delay(10);
//}
