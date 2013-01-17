#include "ofxIpVideoServerRouteHandler.h"

//------------------------------------------------------------------------------
ofxIpVideoServerRouteHandler::Settings::Settings() {
    quality      = OF_IMAGE_QUALITY_MEDIUM;
    
//    streamTimeout = 1000 * 60; // 1 minute for a stream to time out
    
    route.path  = "/video";
    
    boundary = "--boundary";
    
    frameSleep = 10; // ms
    
}

//------------------------------------------------------------------------------
ofxIpVideoServerRouteHandler::ofxIpVideoServerRouteHandler(const Settings& _settings, ofPtr<ofxIpVideoServerFrameQueue> _queue) : settings(_settings), queue(_queue) { }

//------------------------------------------------------------------------------
ofxIpVideoServerRouteHandler::~ofxIpVideoServerRouteHandler() {
    
    ofLogVerbose("ofxIpVideoServerRouteHandler::~ofxIpVideoServerRouteHandler") << "Destroyed.";
}

//------------------------------------------------------------------------------
void ofxIpVideoServerRouteHandler::handleRequest(HTTPServerRequest& request,
                                                 HTTPServerResponse& response) {
    
    
    if(isValidRequest(settings.route,request,response)) {
        MediaType mediaType("multipart/x-mixed-replace");
        mediaType.setParameter("boundary", settings.boundary);

        string expires = DateTimeFormatter::format(Timestamp(0), // the beginning of time
                                                   DateTimeFormat::HTTP_FORMAT);
        
        response.set("Cache-control","no-cache");
        response.setContentType(mediaType);
        response.set("Expires",expires);
        response.set("Pragma","no-cache");
        
        std::ostream& ostr = response.send(); // get output stream

        bool stopStreaming = false;
        
        ofBuffer b = ofBufferFromFile("puppy.jpg");
        
        while(ostr.good() && !stopStreaming) {
            
            try {
            
                if(queue != NULL) {
                   // if(!queue->empty()) {
                        //ofxIpVideoServerFramePtr frame = queue->pop();
                        //if(frame != NULL) {
//                            ofBuffer* buffer = &frame.get()->buffer;
                            ostr << settings.boundary;
                            ostr << "\r\n";
                            ostr << "Content-Type: image/jpeg";
                            ostr << "\r\n";
//                            ostr << "Content-Length: " << ofToString(buffer->size());
                            ostr << "Content-Length: " << ofToString(b.size());
                            ostr << "\r\n";
                            ostr << "\r\n";
//                            ostr << *buffer;
                            ostr << b;
//                        } else {
//                            ofLogWarning("ofxIpVideoServerRouteHandler::handleRequest") << "Null buffer.";
//                        }
//                    } else {
//                        ofLogWarning("ofxIpVideoServerRouteHandler::handleRequest") << "Queue empty.";
//                    }
                    
                } else {
                    stopStreaming = true;
                    ostr << "Buffer = NULL";
                    cout << "buffer = null" << endl;
                }
                
            } catch(...) {
                stopStreaming = true;
                cout << "CAUGHT ERROR" << endl;
            }

            if(!ostr.good()) {
                cout << "STREAM WENT BAD" << endl;
            }
            
            Thread::sleep(50);
        }
        
        queue->setActive(false);
        
        cout << "Dead" << endl;
        
        //sendErrorResponse(response);
    }
}