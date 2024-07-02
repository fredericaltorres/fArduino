

// fESP32.h

#ifndef _HTTPMANAGER_h
#define _HTTPMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// C:\Users\ftorres\OneDrive - Brainshark, Inc\Documents\Arduino\libraries\TFT_eSPI\examples\PNG Images\Flash_PNG
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HttpManager
///
class HttpManager {

private:
    
public:
    int StatusCode;
    String Content;
    int _binaryBufferLen;

    HttpManager();
    ~HttpManager();
    bool Get(String url, String hdrName, String hdrValue);
    bool GetImage(String url, String hdrName, String hdrValue);
    bool Post(String url, String body);
};

#endif

