

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "HTTPManager.h"
#include "HTTPManager.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HttpManager
/// https://randomnerdtutorials.com/esp32-http-get-post-arduino/
/// https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.cpp#L309

HttpManager::HttpManager() {

}
HttpManager::~HttpManager() {
}
bool HttpManager::Get(String url, String hdrName, String hdrValue) {

    bool r = false;
    HTTPClient http;
    http.begin(url.c_str());
    if (!hdrName.isEmpty()) {
        http.addHeader(hdrName, hdrValue);
    }
    this->StatusCode = http.GET();

    if (this->StatusCode >= 200 && this->StatusCode <= 299) {
        this->Content = http.getString();
        r = true;
    }
    http.end();
    return r;
}

#define BUFF_SIZE (1024 * 1)

bool HttpManager::GetImage(String url, String hdrName, String hdrValue) {

    bool r = false;
    HTTPClient http;
    http.begin(url.c_str());
    if (!hdrName.isEmpty()) {
        http.addHeader(hdrName, hdrValue);
    }
     byte buff [BUFF_SIZE] = { 0 };
     byte buff2[BUFF_SIZE] = { 0 };
     // byte * buff2 = (byte*)malloc(BUFF_SIZE*51); // Alloc a buffer of 51 k

    int tmpBuffSize = 1024;
    int tmpBuffOffset = 0;
    this->StatusCode = http.GET();
    if (this->StatusCode >= HTTP_CODE_OK && this->StatusCode <= 299)
    {
        this->_binaryBufferLen = http.getSize();
        int len = this->_binaryBufferLen;
        WiFiClient * stream = http.getStreamPtr();
        int fetchCounter = 0;
        while (http.connected() && (len > 0 || len == -1))
        {
            size_t size = stream->available(); // Read 2k or less
            // int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
            int c = stream->readBytes(buff, ((size > tmpBuffSize) ? tmpBuffSize : size));
            // memcpy((void*)buff2, buff, 1024);
            /// tmpBuffOffset += c;
            if (len > 0) {
                len -= c;
            }
            fetchCounter += 1;
        }
        this->_binaryBufferLen = fetchCounter;
        r = true;
    }
    http.end();
    return r;
}

bool HttpManager::Post(String url, String body) {

    bool r = false;
    HTTPClient http;
    http.begin(url.c_str());
    http.setTimeout(60*1000);
    http.addHeader("Content-Type", "application/json");
    this->StatusCode = http.POST(body);

    if (this->StatusCode >= 200 && this->StatusCode <= 299) {
        this->Content = http.getString();
        r = true;
    }
    http.end();
    return r;
}

