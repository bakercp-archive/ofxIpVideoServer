//
//  ofThreadErrorHandler.h
//  example
//
//  Created by Christopher P. Baker on 1/13/13.
//
//

#pragma once

#include "ofLog.h"

#include "Poco/ErrorHandler.h"

using Poco::ErrorHandler;

class ofThreadErrorHandler : public ErrorHandler {
public:
    
    ofThreadErrorHandler(const string& _threadName = "NONE") {
        threadName = _threadName;
    }
    
    virtual ~ofThreadErrorHandler() { }
    
    void exception(const Poco::Exception& exc) {
        ofLogError("ofThreadErrorHandler::exception") << "Uncaught thread exception: " << exc.displayText();
    }
    
    void exception(const std::exception& exc) {
        ofLogError("ofThreadErrorHandler::exception") << "Uncaught thread exception: " << exc.what();
    }
    void exception() {
        ofLogError("ofThreadErrorHandler::exception") << "Uncaught thread exception: Unknown exception.";
    }
    
    void setName(const string& name) {
        threadName = name;
    }
    
    string getName() const {
        return threadName;
    }
    
private:
    string threadName;
};