#include "ofxIpVideoServerFrame.h"

//------------------------------------------------------------------------------
ofxIpVideoServerFrame::Settings::Settings() {
    width           = -1;
    height          = -1;
    bFlipHorizontal = false;
    bFlipVertical   = false;
    fps             = 30.0f;
    quality         = OF_IMAGE_QUALITY_MEDIUM;
}

//------------------------------------------------------------------------------
ofxIpVideoServerFrame::ofxIpVideoServerFrame(ofBuffer& _buffer,
                                             unsigned long long _timestamp,
                                             const Settings& _settings) {
    buffer = _buffer;
    settings = _settings;
    timestamp = _timestamp;
}

//------------------------------------------------------------------------------
ofxIpVideoServerFrame::~ofxIpVideoServerFrame() {
    
}