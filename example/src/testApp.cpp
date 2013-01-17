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
void testApp::setup() {
    
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
        
    video.loadMovie("DocumentRoot/fingers.mov");
    video.play();
    
    ofxIpVideoServer::Settings settings;

    settings.server.port = 8989;
    settings.server.host = "http://127.0.0.1";
        
    server = new ofxIpVideoServer(settings);

    server->addRoute(ofHttpServerDefaultRoute::Instance());
    server->addRoute(ofHttpServerUploadRoute::Instance());

    ofxIpVideoServerRouteHandler::Settings videoRouteSettings;
    settings.route.path = "/video";
    
    videoRoute = ofxIpVideoServerRoute::Instance(videoRouteSettings);
    server->addRoute(videoRoute);

    server->start();

    ofLaunchBrowser(server->getURL());
    ofLaunchBrowser(server->getURL() + "video");
}

//--------------------------------------------------------------
void testApp::update() {
    video.update();

    if(video.isFrameNew()) {
        videoRoute->pushFrame(video.getPixelsRef());
    }
    
}

//--------------------------------------------------------------
void testApp::draw() {
    video.draw(0,0);
}


