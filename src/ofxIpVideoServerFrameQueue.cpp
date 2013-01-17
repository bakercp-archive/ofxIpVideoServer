#include "ofxIpVideoServerFrameQueue.h"

//------------------------------------------------------------------------------
ofxIpVideoServerFrameQueue::ofxIpVideoServerFrameQueue(const ofxIpVideoServerFrame::Settings& _settings, size_t _maxSize) : settings(_settings), maxSize(_maxSize), active(true) { }

//------------------------------------------------------------------------------
ofxIpVideoServerFrameQueue::~ofxIpVideoServerFrameQueue() {
    active = false;
    ofScopedLock lock(mutex);
    
}

//------------------------------------------------------------------------------
ofxIpVideoServerFramePtr ofxIpVideoServerFrameQueue::pop() {
    ofxIpVideoServerFramePtr frame;
    if(!active) return frame;
    ofScopedLock lock(mutex);
    frame = frames.front();
    frames.pop();
    return frame;
}

//------------------------------------------------------------------------------
void ofxIpVideoServerFrameQueue::push(ofxIpVideoServerFramePtr frame) {
    if(!active) return;
    ofScopedLock lock(mutex);
    frames.push(frame);
    while(frames.size() > maxSize) frames.pop();
}

//------------------------------------------------------------------------------
size_t ofxIpVideoServerFrameQueue::getMaxSize() const {
    return maxSize;
}

//------------------------------------------------------------------------------
void ofxIpVideoServerFrameQueue::setMaxSize(size_t _maxSize) {
    if(!active) return;
    ofScopedLock lock(mutex);
    maxSize = _maxSize;
    while(frames.size() > maxSize) frames.pop();
}

//------------------------------------------------------------------------------
size_t ofxIpVideoServerFrameQueue::size() const {
    return frames.size();
}

//------------------------------------------------------------------------------
bool ofxIpVideoServerFrameQueue::empty() const {
    return frames.empty();
}

//------------------------------------------------------------------------------
bool ofxIpVideoServerFrameQueue::isActive() {
    return active;
}

//------------------------------------------------------------------------------
void ofxIpVideoServerFrameQueue::setActive(bool _active) {
    active = _active;
}
