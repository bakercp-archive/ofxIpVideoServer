#include "ofxIpVideoServerRoute.h"

//------------------------------------------------------------------------------
ofxIpVideoServerRoute::ofxIpVideoServerRoute(const ofxIpVideoServerRouteHandler::Settings& _settings) : settings(_settings) {
    lastUpdated = 0;    
}

//------------------------------------------------------------------------------
ofxIpVideoServerRoute::~ofxIpVideoServerRoute() { }

//------------------------------------------------------------------------------
HTTPRequestHandler* ofxIpVideoServerRoute::createRequestHandler(const HTTPServerRequest& request) {

    URI uri(request.getURI());
    
    if(ofxIpVideoServerRouteHandler::matchRoute(uri,settings.route)) {
        
        ofxIpVideoServerFrame::Settings targetSettings;
        
        string query = uri.getQuery();
        
        NameValueCollection queryMap = ofGetQueryMap(uri);
    
        if(queryMap.has("vflip")) {
            string vflip = queryMap.get("vflip");
            targetSettings.bFlipVertical = icompare(vflip,"1")    == 0 ||
                                           icompare(vflip,"true") == 0 ||
                                           icompare(vflip,"t")    == 0 ||
                                           icompare(vflip,"y")    == 0 ||
                                           icompare(vflip,"yes")  == 0;
        }
        
        if(queryMap.has("hflip")) {
            string hflip = queryMap.get("hflip");
            targetSettings.bFlipHorizontal = icompare(hflip,"1")    == 0 ||
                                             icompare(hflip,"true") == 0 ||
                                             icompare(hflip,"t")    == 0 ||
                                             icompare(hflip,"y")    == 0 ||
                                             icompare(hflip,"yes")  == 0;
        }
        
        if(queryMap.has("size")) {
            string size = queryMap.get("size");
            toLowerInPlace(size);
            vector<string> tokens = ofSplitString(size,"x");
            if(tokens.size() == 2) {
                int width = ofToInt(tokens[0]);
                int height = ofToInt(tokens[1]);
                
                if(width > 0 && height > 0) {
                    width = MIN(width,MAX_VIDEO_DIM);
                    height = MIN(height,MAX_VIDEO_DIM);
                    targetSettings.width  = width;
                    targetSettings.height = height;
                }
            }
        }
        
        if(queryMap.has("quality")) {
            string quality = queryMap.get("quality");
            if(icompare(quality,"best")) {
                targetSettings.quality = OF_IMAGE_QUALITY_BEST;
            } else if(icompare(quality,"high")) {
                targetSettings.quality = OF_IMAGE_QUALITY_HIGH;
            } else if(icompare(quality,"medium")) {
                targetSettings.quality = OF_IMAGE_QUALITY_MEDIUM;
            } else if(icompare(quality,"low")) {
                targetSettings.quality = OF_IMAGE_QUALITY_LOW;
            } else if(icompare(quality,"worst")) {
                targetSettings.quality = OF_IMAGE_QUALITY_WORST;
            } else {
                // no change
            }
        }
        
        ofxIpVideoServerFrameQueue* queue = new ofxIpVideoServerFrameQueue(targetSettings);
        
        queues.push_back(queue);
        
        return new ofxIpVideoServerRouteHandler(settings,*queue);
    } else {
        return NULL;
    }
}

//------------------------------------------------------------------------------
void ofxIpVideoServerRoute::pushFrame(ofPixels& pix) {

    int sz = queues.size();

//    ofRemove(queues,queueIsNULL);
    
    int sz2 = queues.size();
    if(sz != sz2) {
        cout << "removed one!!!!!!!!!!!!!!!" << endl;
    }
    
    if(pix.isAllocated()) {
        unsigned long long timestamp = ofGetElapsedTimeMillis();
        ofPixels pixels(pix); // copy the pixels
        ofSaveImage(pixels, buffer, OF_IMAGE_FORMAT_JPEG, settings.quality);
        
        vector<ofxIpVideoServerFrameQueue*>::iterator iter = queues.begin();
        
        ofxIpVideoServerFrame::Settings settings;
        settings.quality = settings.quality;
        
        ofxIpVideoServerFramePtr frame = ofxIpVideoServerFramePtr(new ofxIpVideoServerFrame(buffer,
                                                                                            timestamp,
                                                                                            settings));

        while(iter != queues.end()) {
            if((*iter) != NULL && (*iter)->isActive()) {
                (*iter)->push(frame);
            }
            ++iter;
        }
            
    } else {
        ofLogError("ofxIpVideoServerRoute::pushFrame") << "Pushing unallocated pixels.";
    }
}

////------------------------------------------------------------------------------
//void ofxIpVideoServerRoute::pushFrame(ofFloatPixels& pix) {
//    if(pix.isAllocated()) {
//        ofFloatPixels pixels(pix); // copy the pixels
//        ofSaveImage(pixels, doubleBuffer[ci^1], OF_IMAGE_FORMAT_JPEG, settings.quality);
//        flipBuffer();
//    } else {
//        ofLogError("ofxIpVideoServerRoute::pushFrame") << "Pushing unallocated pixels.";
//    }
//}
//
////------------------------------------------------------------------------------
//void ofxIpVideoServerRoute::pushFrame(ofShortPixels& pix) {
//    if(pix.isAllocated()) {
//        ofShortPixels pixels(pix);
//        ofSaveImage(pixels, doubleBuffer[ci^1], OF_IMAGE_FORMAT_JPEG, settings.quality);
//        flipBuffer();
//    } else {
//        ofLogError("ofxIpVideoServerRoute::pushFrame") << "Pushing unallocated pixels.";
//    }
//}
//
////------------------------------------------------------------------------------
//void ofxIpVideoServerRoute::pushFrame(ofImage& img) {
//    pushFrame(img.getPixelsRef());
//}
//
////------------------------------------------------------------------------------
//void ofxIpVideoServerRoute::pushFrame(ofFloatImage& img) {
//    pushFrame(img.getPixelsRef());
//}
//
////------------------------------------------------------------------------------
//void ofxIpVideoServerRoute::pushFrame(ofShortImage& img) {
//    pushFrame(img.getPixelsRef());
//}

//------------------------------------------------------------------------------
ofxIpVideoServerRoute* ofxIpVideoServerRoute::Instance(const ofxIpVideoServerRouteHandler::Settings& settings) {
    return new ofxIpVideoServerRoute(settings);
}