#include "ofxIpVideoServer.h"

//------------------------------------------------------------------------------
ofxIpVideoServer::Settings::Settings() {

}

//------------------------------------------------------------------------------
ofxIpVideoServer::ofxIpVideoServer(const Settings& settings) : ofHttpServer(settings.server) { }

//------------------------------------------------------------------------------
ofxIpVideoServer::~ofxIpVideoServer() { }

