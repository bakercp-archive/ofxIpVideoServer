#include "ofHttpServerDefaultRouteHandler.h"

//------------------------------------------------------------------------------
ofHttpServerDefaultRouteHandler::Settings::Settings() {
    defaultIndex = "index.html";
    route.path   = "/.*"; // regex
    
}

//------------------------------------------------------------------------------
ofHttpServerDefaultRouteHandler::ofHttpServerDefaultRouteHandler(const Settings& _settings) : settings(_settings) { }

//------------------------------------------------------------------------------
ofHttpServerDefaultRouteHandler::~ofHttpServerDefaultRouteHandler() { }

//------------------------------------------------------------------------------
void ofHttpServerDefaultRouteHandler::handleRequest(HTTPServerRequest& request,
                                                    HTTPServerResponse& response) {
    
    if(isValidRequest(settings.route, request, response)) {
        
        URI uri(request.getURI());
        
        string path = uri.getPath(); // just get the path
        
        ofLogVerbose("ofHttpServerDefaultRouteHandler::handleRequest") << "request: " << request.getURI();
        
        if(path == "/") { path = "/" + settings.defaultIndex;} // default index
        
        ofFile file(settings.route.documentRoot + path);
        string absolutePath = file.getAbsolutePath();
        string fileExtension = file.getExtension();
        
        try {
            MediaType mediaType = ofHttpServerGetMimeType(fileExtension);
            response.sendFile(absolutePath, mediaType.toString());
        } catch (const Poco::FileNotFoundException& ex) {
            response.setStatusAndReason(HTTPResponse::HTTP_NOT_FOUND);
            ofLogError("ofHttpServerDefaultRouteHandler::handleRequest") << ex.displayText();
        } catch (const Poco::OpenFileException& ex) {
            response.setStatusAndReason(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            ofLogError("ofHttpServerDefaultRouteHandler::handleRequest") << ex.displayText();
        } catch (const std::exception& ex) {
            response.setStatusAndReason(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            ofLogError("ofHttpServerDefaultRouteHandler::handleRequest") << "Unknown server error: " << ex.what();
        }
        
        if(response.getStatus() != HTTPResponse::HTTP_OK) {
            sendErrorResponse(settings.route,response);
        }
    }
    
}