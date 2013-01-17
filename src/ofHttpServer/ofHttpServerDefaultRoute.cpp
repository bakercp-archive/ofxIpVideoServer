#include "ofHttpServerDefaultRoute.h"

//------------------------------------------------------------------------------
ofHttpServerDefaultRoute::ofHttpServerDefaultRoute(const ofHttpServerDefaultRouteHandler::Settings& _settings) : settings(_settings) {
    ofDirectory documentRootDirectory(settings.route.documentRoot);
    if(!documentRootDirectory.exists()) {
        ofLogNotice("ofHttpServerDefaultRoute::ofHttpServerDefaultRoute") << "Document Root directory did not exist.  Creating: " << documentRootDirectory.getAbsolutePath();
        documentRootDirectory.create();
    }

}

//------------------------------------------------------------------------------
ofHttpServerDefaultRoute::~ofHttpServerDefaultRoute() { }

//------------------------------------------------------------------------------
HTTPRequestHandler* ofHttpServerDefaultRoute::createRequestHandler(const HTTPServerRequest& request) {
    if(ofHttpServerDefaultRouteHandler::matchRoute(URI(request.getURI()), settings.route)) {
        return new ofHttpServerDefaultRouteHandler(settings);
    } else {
        cout << "unhandled route == > " << request.getURI() << " - " << settings.route.path << endl;
        return NULL;
    }
}

//------------------------------------------------------------------------------
ofHttpServerDefaultRoute* ofHttpServerDefaultRoute::Instance(const ofHttpServerDefaultRouteHandler::Settings& settings) {
    return new ofHttpServerDefaultRoute(settings);
}
