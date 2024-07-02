#include "Arduino.h"
// #include "TFT_eSPI.h"/* Please use the TFT library provided in the library. */
#include "C:\Users\ftorres\OneDrive - Brainshark, Inc\Documents\Arduino\libraries\TFT_eSPI\TFT_eSPI.h"/* Please use the TFT library provided in the library. */
#include <WiFi.h>
#include "time.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "fESP32.h"
#include "ScreenManager.h"
#include "AuthoringPresentation.h"

// https://github.com/Bodmer/TFT_eWidget
// https://github.com/Bodmer/TFT_eSPI


TFT_eSPI lcd = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&lcd); 

const char* ssid = "Fios-hQLr4";
const char* password = "cob78yaw222swank";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

char timeHour[3] = "00";
char timeMin[3] = "00";
char timeSec[3];

char m[12];
char y[5];
char d[3];
char dw[12];

//int gw = 204;
//int gh = 102;
//int gx = 110;
//int gy = 144;
//int curent = 0;
#define gray 0x6B6D
#define blue 0x0967
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9

int deb = 0;
int Mode = 0;
#define RIGHT 14
#define LEFT 0

#define LED_PIN 2

ScreenManager               _screenManager(&sprite);
Led                         _onBoardLed(LED_PIN);
TimeOut                     _timeAcquisitionTimeOut(1 * 1000);
HttpManager                 _httpManager;
AuthoringPresentation       _authoringPresentation(&_httpManager);

bool _authoringPresentationLoaded = false;

void Trace(char* s) {

    Serial.println(s);
}

void LcdInit() {
    lcd.init();
    lcd.fillScreen(TFT_BLACK);
    lcd.setRotation(1); // [ ]   Width 320 Height 170
}

void WifiInit() {

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Trace("WiFi connected.");
}

void setup(void) {

    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);

    Serial.begin(115200);
    Trace("Starting...");

    _screenManager.Init();
    _screenManager.DrawWindow("Brainshark Presentation MicroController");
    _screenManager.DrawText("Initializing");

    _onBoardLed.SetBlinkMode(1 * 1000);
    pinMode(RIGHT, INPUT_PULLUP);

    _screenManager.DrawText("Initializing LCD");
    LcdInit();

    _screenManager.DrawText("Initializing WIFI");
    WifiInit();

    if (_authoringPresentation.GetSessionToken()) {
        _screenManager.DrawText("SessionToken acquired");
    }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    analogReadResolution(10);
    _screenManager.DrawText("Ready");
}

int counter     = 0;
int average     = 0;
String minT     = "";
long lastMillis = 0;
int fps         = 0;
bool displayTimeModeOn = true;

void loop()
{
    _onBoardLed.Blink();

    if (digitalRead(RIGHT) == 0)
    {
        displayTimeModeOn = true;
        _screenManager.Clear();
    }
    int pid = 989234928;
    if (digitalRead(LEFT) == 0)
    {
        if (!_authoringPresentationLoaded) {

            displayTimeModeOn = false;
            _screenManager.Clear();
            _screenManager.DrawStatus("Loading PresentationId:" + String(pid));
            if (_authoringPresentation.Get(pid)) 
            {
                _screenManager.DrawText(_authoringPresentation.ToString(0));
                _screenManager.DrawText(_authoringPresentation.ToString(1));
                _screenManager.DrawText(_authoringPresentation.ToString(2));
                _screenManager.DrawText(_authoringPresentation.ToString(3));
                _screenManager.DrawStatus("Loaded PresentationId: " + String(pid));
                _authoringPresentationLoaded = true;
            }
            else 
            {
                _screenManager.DrawStatus("Error: " + String(_authoringPresentation.StatusCode), true);
            }
        }
        else 
        {
            _screenManager.DrawStatus("Loading Thumbnail PresentationId:" + String(pid));
            if (_authoringPresentation.GetThumbnail()) {
                _screenManager.DrawText("GetThumbnail ok "+ String(_authoringPresentation.StatusCode));
            }
            else {
                _screenManager.DrawStatus("GetThumbnail Error: " + String(_authoringPresentation.StatusCode), true);
            }
        }
        
        //if (_httpManager.Get(url, "Brainshark-STok", sessionToken))
        //{
        //     /*JSONVar myObject = JSON.parse(_httpManager.Content);
        //     _screenManager.DrawText("OK");

        //     if (myObject.hasOwnProperty("presentationId")) {
        //         int pid = (int)myObject["presentationId"];
        //         _screenManager.DrawText("  pid:" + String(pid));
        //     }
        //     if (myObject.hasOwnProperty("title")) {
        //         String title = (const char*)myObject["title"];
        //         _screenManager.DrawText("  title:" + title);
        //     }*/
        //}
        //else {
        //    _screenManager.DrawText("Error:" + String(_httpManager.StatusCode));
        //}
        //
        /*
        String url = String("https://wwwqaz1.brainshark.com/brainshark/webservices_mobile/session.ashx");
        String body = String("{'username':'IntegrationTesting_Converters_Cheetah_Company_06_Admin','password':'moxie','login_dir':'IntegrationTesting_Converters_Cheetah_Company_06','detailedlogging':true}");
        body.replace("'", "\"");
        _screenManager.DrawText("url:" + url);
        _screenManager.DrawText("body:" + body);
        if (_httpManager.Post(url, body))
        {
            _screenManager.DrawText(_httpManager.Content);
        }
        else {
            _screenManager.DrawText("Error:" + String(_httpManager.StatusCode));
        }*/

        /*if (_httpManager.Get("https://flogviewer.blob.core.windows.net/build/Version.cs")) {
            _screenManager.DrawText(_httpManager.Content);
        }
        else {
            _screenManager.DrawText("Error");
        }*/
    }

    if (_timeAcquisitionTimeOut.IsTimeOut() && displayTimeModeOn)
    {
        AcquireLocalTime();
        String maxT = String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec);
        _screenManager.DrawText(maxT);
        //Trace((char *)maxT.c_str());
        int analogPotValue = analogRead(A0); // PIN 1
        _screenManager.DrawText("ADC: "+ String(analogPotValue));
    }
    
    //minT = String(timeHour) + ":" + String(timeMin) + ":" + String(timeSec);
   
    //sprite.fillSprite(TFT_BLACK);
    //// sprite.setTextDatum(4);
    //sprite.setTextColor(TFT_WHITE, blue);
    //sprite.fillRoundRect(6, 5, 38, 32, 4, blue);
    //
    //sprite.drawString(String(timeHour), 10, 24, 4);
    //sprite.drawString(String(timeMin), 56, 24, 4);
    //sprite.drawString(String(m) + " " + String(d), 10, 48);

    //sprite.drawString(String(timeSec), gx - 14, 14, 2);
    //sprite.setTextColor(TFT_WHITE, purple);
    //sprite.drawString("MIN: " + String(Min), 10, 108, 2);
    //sprite.drawString("MAX: " + String(Max), 10, 138, 2);

    //sprite.setTextColor(TFT_SILVER, purple);
    //sprite.drawString(String(maxT), 10, 152);
    //sprite.drawString(String(minT), 10, 122);
    //sprite.setTextColor(TFT_WHITE, green);
    //sprite.drawString("SPEED:" + String(fps) + " fps", 10, 68);
    //sprite.setTextColor(TFT_YELLOW, TFT_BLACK);
    //sprite.drawString("ANALOG READINGS", gx + 10, 16, 2);
    //sprite.drawString("ON PIN 12", gx + 10, 30);
    //sprite.setFreeFont();
    //sprite.pushSprite(0, 0);
    //delay(1000);


    //int delayTime = 500;
    //_screenManager.Clear(); delay(delayTime);
    //_screenManager.DrawWindow("Fred's Device");
    //_screenManager.DrawText("Hello world...");delay(delayTime);
    //_screenManager.DrawText("Connecting to endpoint");delay(delayTime);
    //_screenManager.DrawText("Connected");delay(delayTime);
    //_screenManager.DrawText("Connected..."); delay(delayTime);
    //_screenManager.Clear(); delay(delayTime);

    //for (int i = 0; i < 10; i++) {
    //    _screenManager.DrawText("Line: " + String(i)); delay(1000);
    //}
}

void AcquireLocalTime() {

    // C:\Users\ftorres\AppData\Local\arduino15\packages\esp32\hardware\esp32\2.0.5\cores\esp32
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }

    strftime(timeHour, 3, "%H", &timeinfo);
    strftime(timeMin, 3, "%M", &timeinfo);
    strftime(timeSec, 3, "%S", &timeinfo);
    strftime(y, 5, "%Y", &timeinfo);
    strftime(m, 12, "%B", &timeinfo);
    strftime(dw, 10, "%A", &timeinfo);
    strftime(d, 3, "%d", &timeinfo);
}
