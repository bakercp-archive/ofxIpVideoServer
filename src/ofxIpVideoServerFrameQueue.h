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

#include <queue>

#include "Poco/Condition.h"

#include "ofTypes.h"

#include "ofxIpVideoServerFrame.h"

using std::queue;

using Poco::Condition;

typedef ofMutex::ScopedLock ofScopedLock;

class ofxIpVideoServerFrameQueue {
public:
    
    ofxIpVideoServerFrameQueue(const ofxIpVideoServerFrame::Settings& _settings, size_t _maxSize = 15);
    virtual ~ofxIpVideoServerFrameQueue();

    ofxIpVideoServerFramePtr pop();
    
    void push(ofxIpVideoServerFramePtr frame);

    size_t getMaxSize() const;
    void   setMaxSize(size_t _maxSize);
    size_t size() const;
    bool   empty() const;
    
    bool   isActive();
    void   setActive(bool active);
    
private:
    
    bool active;
    
    size_t maxSize;
    
    ofxIpVideoServerFrame::Settings settings;
    
    queue<ofxIpVideoServerFramePtr> frames;
    
    ofMutex mutex;
    
};
