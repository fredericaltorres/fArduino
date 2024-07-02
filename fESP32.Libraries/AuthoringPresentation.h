

// _AuthoringPresentation.h

#ifndef _AuthoringPresentation_h
#define _AuthoringPresentation_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AuthoringPresentation
///
/// C:\Users\ftorres\OneDrive - Brainshark, Inc\Documents\Arduino\libraries\Arduino_JSON\examples\JSONObject\JSONObject.ino
class AuthoringPresentation {

private:
   String _sessionToken;
   HttpManager* _httpManager;

public:
   int StatusCode;

   int presentationId;
   int authorID;
   int duration;
   String title;
   String description;
   String lastUpdated;
   
   AuthoringPresentation(HttpManager * httpManager);
   ~AuthoringPresentation();
   bool Get(int pid);
   bool GetSessionToken();
   bool GetThumbnail();
   String ToString(int lineIndex);
};

#endif

