#include "ofHttpServerUploadRoute.h"

//------------------------------------------------------------------------------
ofHttpServerUploadRoute::ofHttpServerUploadRoute(const ofHttpServerUploadRouteHandler::Settings& _settings) : settings(_settings) {
    ofDirectory uploadsDirectory(settings.uploadFolder);
    if(!uploadsDirectory.exists()) {
        ofLogNotice("ofHttpServerUploadRoute::ofHttpServerUploadRoute") << "Uploads directory did not exist.  Creating: " << uploadsDirectory.getAbsolutePath();
        uploadsDirectory.create();
    }
}
    
//------------------------------------------------------------------------------
ofHttpServerUploadRoute::~ofHttpServerUploadRoute() { }
    
//------------------------------------------------------------------------------
HTTPRequestHandler* ofHttpServerUploadRoute::createRequestHandler(const HTTPServerRequest& request) {
    // this will respond to anything
    if(ofHttpServerUploadRouteHandler::matchRoute(URI(request.getURI()), settings.route)) {
        return new ofHttpServerUploadRouteHandler(settings);
    } else {
        return NULL;
    }
}

//------------------------------------------------------------------------------
ofHttpServerUploadRoute* ofHttpServerUploadRoute::Instance(const ofHttpServerUploadRouteHandler::Settings& settings) {
    return new ofHttpServerUploadRoute(settings);
}