#include "ofHttpServerRouteManager.h"

//------------------------------------------------------------------------------
ofHttpServerRouteManager::ofHttpServerRouteManager(vector< HTTPRequestHandlerFactory* >& _factories) : factories(_factories) { }

//------------------------------------------------------------------------------
ofHttpServerRouteManager::~ofHttpServerRouteManager() { }
    
//------------------------------------------------------------------------------
HTTPRequestHandler* ofHttpServerRouteManager::createRequestHandler(const HTTPServerRequest& request) {
    if(!factories.empty()) {
        vector< HTTPRequestHandlerFactory* >::reverse_iterator iter = factories.rbegin();
        // We start with the last factory that was added.
        while(iter != factories.rend()) {
            HTTPRequestHandler* handler = (*iter)->createRequestHandler(request);
            if(handler != NULL) {
                // If we were given a valid handler pointer, we can
                // return it (the server will own it and destroy it).
                return handler;
            } else {
                ++iter;
            }
        }
    } else {
        ofLogError("ofHttpServerRequestHandlerFactory::createRequestHandler") << "The handler factories list was empty.";
    }
    
    return new ofHttpServerFailedRouteHandler(); // if we get to this point, we got a fail.
}