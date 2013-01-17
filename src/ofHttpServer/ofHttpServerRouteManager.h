#pragma once

#include <vector>

#include "Poco/Net/HTTPRequestHandlerFactory.h"

#include "ofTypes.h"

#include "ofHttpServerFailedRouteHandler.h"

using std::vector;

using Poco::Net::HTTPRequestHandlerFactory;

//------------------------------------------------------------------------------
class ofHttpServerRouteManager : public HTTPRequestHandlerFactory {
public:
    ofHttpServerRouteManager(vector< HTTPRequestHandlerFactory* >& _factories);
    virtual ~ofHttpServerRouteManager();
    
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);
    
protected:
    vector< HTTPRequestHandlerFactory* >& factories;
};
