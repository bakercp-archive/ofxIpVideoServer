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
