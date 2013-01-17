#include "ofHttpServer.h"

//------------------------------------------------------------------------------
ofHttpServer::Settings::Settings() {
    
    host = "http://127.0.0.1";
    port = 7777;
    
    maxQueued            = 64;
    maxThreads           = 64;
    keepAlive            = true;
    maxKeepAliveRequests = 0; // 0 is unlimited
    keepAliveTimeout     = Timespan(10,0); // 10 seconds
    name                 = ""; // empty, will be auto generated
    softwareVersion      = "ofHttpServer/1.0";
    timeout              = Timespan(60,0); // 60 seconds
    threadIdleTime       = Timespan(10,0);
    threadPriority       = Thread::PRIO_NORMAL;
    
}

//------------------------------------------------------------------------------
ofHttpServer::ofHttpServer(Settings _settings) {
    
    settings = _settings;
    
    previousErrorHandler = NULL;
    errorHandler.setName(settings.name);
    
    ofAddListener(ofEvents().exit,this,&ofHttpServer::exit);
    
    server = NULL;
}

//------------------------------------------------------------------------------
ofHttpServer::~ofHttpServer() {
    stop();
    ofLogVerbose("ofHttpServer::~ofHttpServer") << "Server destroyed.";
}

void ofHttpServer::exit(ofEventArgs& args) {
    ofLogVerbose("ofHttpServer::exit") << "Waiting for thread cleanup.";
    
    stop();
    // it is ok to unregister an item that is not currently registered
    // POCO's internal loop won't complain or return errors
    // POCO stores the delegates in a std::vector and iterates through
    // deleting and returning on match, and doing nothing on a no-match condition
    ofRemoveListener(ofEvents().exit,this,&ofHttpServer::exit);
    ofLogVerbose("ofHttpServer::exit") << "Exit.";
    
}

//------------------------------------------------------------------------------
void ofHttpServer::start(){
    if(server != NULL) {
        ofLogWarning("ofHttpServer::start") << "Server is already running.  Call stop() to stop.";
        return;
    }
    
    
    
    
    // all of these params are an attempt to make the server shut down VERY quickly.
    
    string serverName = settings.name.empty() ? settings.host + ":" + ofToString(settings.port) : settings.name;
    
    HTTPServerParams* serverParams = new HTTPServerParams();
    serverParams->setMaxQueued(settings.maxQueued);
    serverParams->setMaxThreads(settings.maxThreads);
    serverParams->setKeepAlive(settings.keepAlive);
    serverParams->setMaxKeepAliveRequests(settings.maxKeepAliveRequests);
    serverParams->setKeepAliveTimeout(settings.keepAliveTimeout);
    serverParams->setServerName(serverName);
    serverParams->setTimeout(settings.timeout);
    serverParams->setThreadIdleTime(settings.threadIdleTime);
    serverParams->setThreadPriority(settings.threadPriority);
    serverParams->setSoftwareVersion(settings.softwareVersion);
    
    // we use the default thread pool
    server = new HTTPServer(ofxIpVideoServerRoute::Instance(),//new ofHttpServerRouteManager(routes),
                            ServerSocket(settings.port),
                            serverParams);

    
    errorHandler.setName(serverName);
    previousErrorHandler = ErrorHandler::set(&errorHandler);
    
    // start the http server
    server->start();

}

//------------------------------------------------------------------------------
void ofHttpServer::stop() {
    if(server == NULL) {
        ofLogWarning("ofHttpServer::stop") << "Server is not running.  Call start() to start.";
        return;
    }

    server->stop();
    
    // wait for all threads in the thread pool
    ThreadPool::defaultPool().joinAll(); // we gotta wait for all of them ... ugh.
    
    ErrorHandler::set(previousErrorHandler);
    
    ofLogVerbose("ofHttpServer::threadedFunction") << "Server successfully shut down.";
    
    server = NULL;
}

//------------------------------------------------------------------------------
string ofHttpServer::getURL() const {
    stringstream ss;
    ss << settings.host << ":" << settings.port << "/";
    return ss.str();
}

//------------------------------------------------------------------------------
int ofHttpServer::getPort() const {
    return settings.port;
}

//------------------------------------------------------------------------------
void ofHttpServer::clearRoutes() {
    routes.clear();
}

//------------------------------------------------------------------------------
void ofHttpServer::addRoute(HTTPRequestHandlerFactory* handler) {
    routes.push_back(handler);
}

//------------------------------------------------------------------------------
void ofHttpServer::removeRoute(HTTPRequestHandlerFactory* handler) {
    vector<HTTPRequestHandlerFactory*>::iterator iter = routes.begin();
    while(iter != routes.end()) {
        if(*iter == handler) {
            routes.erase(iter);
        }
    }
}