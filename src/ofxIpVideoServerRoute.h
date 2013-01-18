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

#pragma once

#include "ofImage.h"

#include "ofxWebServerBaseRoute.h"
#include "ofxIpVideoServerRouteHandler.h"

#include "ofxIpVideoServerFrame.h"
#include "ofxIpVideoServerFrameQueue.h"

#define MAX_VIDEO_DIM 1920

//------------------------------------------------------------------------------
class ofxIpVideoServerRoute : public ofxWebServerBaseRoute {
public:
    
    struct Settings;
    
    ofxIpVideoServerRoute(const ofxIpVideoServerRouteHandler::Settings& _settings = ofxIpVideoServerRouteHandler::Settings() );
    virtual ~ofxIpVideoServerRoute();
    
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);

    void pushFrame(ofPixels& pix);
    void pushFrame(ofImage& img);
    
    
    static ofPtr<ofxIpVideoServerRoute> Instance(const ofxIpVideoServerRouteHandler::Settings& settings = ofxIpVideoServerRouteHandler::Settings());
    

protected:
    
    unsigned long long lastUpdated;
    ofBuffer buffer;
    
    vector<ofxIpVideoServerFrameQueue*> queues;
    
    ofxIpVideoServerRouteHandler::Settings settings;
};




