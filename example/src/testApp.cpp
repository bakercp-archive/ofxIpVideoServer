/*==============================================================================
 
 Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#include "testApp.h"

testApp::~testApp() {
    if(server) {
        server->stop();
        delete server;
    }
}

//--------------------------------------------------------------
void testApp::setup(){
//    signal(SIGPIPE, SIG_IGN);
    
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
//    grabber.initGrabber(320,240);

    
    
    ofxIpVideoServer::Settings settings;

    settings.server.port = 8989;
    settings.server.host = "http://127.0.0.1";
        
    server = new ofxIpVideoServer(settings);

    server->addRoute(ofHttpServerDefaultRoute::Instance());
    server->addRoute(ofHttpServerUploadRoute::Instance());
    
    videoRoute = ofxIpVideoServerRoute::Instance();

    server->addRoute(videoRoute);

    server->start();

    ofLaunchBrowser(server->getURL());
}

//--------------------------------------------------------------
void testApp::update() {
//    grabber
//    grabber.update();

//    if(grabber.isFrameNew()) {
//        videoRoute->pushFrame(grabber.getPixelsRef());
//    }
    
}

//--------------------------------------------------------------
void testApp::draw() {
    grabber.draw(0,0);
    
}


