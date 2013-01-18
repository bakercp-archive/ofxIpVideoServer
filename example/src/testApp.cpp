#include "testApp.h"

//--------------------------------------------------------------
void testApp::exit() {
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
    video.setLoopState(OF_LOOP_PALINDROME);
    
    ofxIpVideoServer::Settings settings;
    settings.server.port = 8990;
        
    server = new ofxIpVideoServer(settings);

    ofxIpVideoServerRouteHandler::Settings videoRouteSettings;
    videoRouteSettings.route.path = "/";
    
    videoRoute = ofxIpVideoServerRoute::Instance(videoRouteSettings);
    server->addRoute(videoRoute);

    server->start();

    ofLaunchBrowser(server->getURL());
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




