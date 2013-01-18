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
    
#ifdef USE_GRABBER
    video.initGrabber(1280,720);
#else
    video.loadMovie("DocumentRoot/fingers.mov");
    video.play();
    video.setLoopState(OF_LOOP_PALINDROME);
#endif

    ofSetWindowShape(video.getWidth(),video.getHeight());
    
    server = new ofxIpVideoServer();

    ofxIpVideoServerRouteHandler::Settings settings;
    settings.route.path = "/";
    
    videoRoute = ofxIpVideoServerRoute::Instance(settings);

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




