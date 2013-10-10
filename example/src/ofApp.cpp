// =============================================================================
//
// Copyright (c) 2012-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(15);

    isStreamingGrabber = false;

//    grabber/

    img.loadImage("DocumentRoot/puppy.jpg");


//    grabber.initGrabber(1280,720);

    player.loadMovie("DocumentRoot/fingers.mov");
    player.play();
    player.setLoopState(OF_LOOP_PALINDROME);

//    ofSetWindowShape(video.getWidth(),video.getHeight());

    BasicIPVideoServerSettings settings;
    
    server = BasicIPVideoServer::makeShared();

    server->start();

    ofLaunchBrowser(server->getURL());
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    player.update();

    if(player.isFrameNew())
    {
        ofPixels pixels = player.getPixelsRef();

        server->send(pixels);
    }

//    server->send(img.getPixelsRef());
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
//    img.draw(0,0);
    player.draw(0,0);


    ofDrawBitmapStringHighlight("Num clients connected: " + ofToString(server->getNumConnections()), 20,20);

}


void ofApp::keyPressed(int key)
{
    if(key == ' ')
    {

    }
}

