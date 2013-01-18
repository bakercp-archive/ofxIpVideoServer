#include "ofxIpVideoServer.h"

//------------------------------------------------------------------------------
ofxIpVideoServer::Settings::Settings() {

}

//------------------------------------------------------------------------------
ofxIpVideoServer::ofxIpVideoServer(const Settings& settings) : ofxWebServer(settings.server) { }

//------------------------------------------------------------------------------
ofxIpVideoServer::~ofxIpVideoServer() { }

