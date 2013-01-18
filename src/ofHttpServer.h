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

#include <string>

#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Timespan.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/ServerSocket.h"

#include "ofEvents.h"
#include "ofThread.h"
#include "ofTypes.h"
#include "ofUtils.h"

#include "ofThreadErrorHandler.h"

#include "ofHttpServerRouteManager.h"

using std::string;

using Poco::Thread;
using Poco::ThreadPool;
using Poco::Timespan;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandlerFactory;

//typedef ofPtr<HTTPRequestHandlerFactory> ofHttpServerRoutePtr;

//------------------------------------------------------------------------------
class ofHttpServer {
public:
    struct Settings;

    ofHttpServer(Settings settings = Settings());
    
    virtual ~ofHttpServer();
    void start();
    void stop();
    void threadedFunction();
    
    void exit(ofEventArgs& args);
        
    string getURL() const; // TODO: POCO URI
    int    getPort() const;
    
    void clearRoutes();
    void addDefaultRoute();
    
    void addRoute(HTTPRequestHandlerFactory* route);
    void removeRoute(HTTPRequestHandlerFactory* route);
    
	struct Settings {

        string           host;
        unsigned short   port;
        
        int              maxQueued;
        int              maxThreads;
        bool             keepAlive;
        int              maxKeepAliveRequests;
        Timespan         keepAliveTimeout;
        string           name;
        Timespan         timeout;
        Timespan         threadIdleTime;
        Thread::Priority threadPriority;
        string           softwareVersion;
                
		Settings();
	};
    
protected:
    HTTPServer* server;
    
    Settings settings;

    vector< HTTPRequestHandlerFactory* > routes;
    
    ofThreadErrorHandler errorHandler;
    ErrorHandler* previousErrorHandler;

};
