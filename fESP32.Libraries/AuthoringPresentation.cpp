

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "HTTPManager.h"
#include "AuthoringPresentation.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>

AuthoringPresentation::AuthoringPresentation(HttpManager* httpManager) {
    this->_httpManager = httpManager;
}

AuthoringPresentation::~AuthoringPresentation() {
}

String AuthoringPresentation::ToString(int lineIndex) {
   if (lineIndex == 0) {
       return "pid: " + String(this->presentationId) + " authorID: " + String(this->authorID) + " duraton: " + String(this->duration);
   }
   if (lineIndex == 1)
       return "title: " + this->title;
   if (lineIndex == 2)
       return "description: " + this->description;
   if (lineIndex == 3)
       return "lastUpdated: " + this->lastUpdated;
}



bool AuthoringPresentation::GetSessionToken() {

   String url = "https://fredcloud.blob.core.windows.net/public/sessionToken.txt";
   if (_httpManager->Get(url, "", "")) {
       this->_sessionToken = _httpManager->Content;
   }
   
   return true;
}

bool AuthoringPresentation::Get(int pid) {

   String url = "https://wwwqaz1.brainshark.com/brainshark/brainshark.services.authoring/presentation/"+String(pid);
   if (_httpManager->Get(url, "Brainshark-STok", this->_sessionToken))
   {
       JSONVar myObject = JSON.parse(_httpManager->Content);

       this->presentationId    = (int)myObject["presentationId"];
       this->authorID          = (int)myObject["authorID"];
       this->duration          = (int)myObject["duration"];
       this->title             = (const char*)myObject["title"];
       this->description       = (const char*)myObject["description"];
       this->lastUpdated       = (const char*)myObject["lastUpdated"];

       return true;
   }
   else {
       this->StatusCode = _httpManager->StatusCode;
       return false;
   }
}

bool AuthoringPresentation::GetThumbnail() {

   //String url = "https://wwwqaz1.brainshark.com/brainshark/brainshark.services.authoring/image/presentation/" + String(this->presentationId);
   String url = "https://fredcloud.blob.core.windows.net/public/image.png";
   if (_httpManager->GetImage(url, "", ""))
   {
       this->StatusCode = _httpManager->_binaryBufferLen;
       return true;
   }
   else 
   {
       this->StatusCode = _httpManager->StatusCode;
       return false;
   }
}
