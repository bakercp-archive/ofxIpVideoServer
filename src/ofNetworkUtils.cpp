#include "ofNetworkUtils.h"


//------------------------------------------------------------------------------
string ofGetHostName() {
    return Poco::Environment::nodeName();
}

//------------------------------------------------------------------------------
string ofGetMacAddress() {
    string nodeId = "UNKNOWN";
    
    try {
        nodeId = Environment::nodeId();
    } catch (const SystemException& exc) {
        ofLogError("ofGetMacAddress") << exc.displayText();
        return nodeId;;
    }
    
    return nodeId;;
}

//------------------------------------------------------------------------------
ofHostEntry ofGetHostByName(const string& hostname) {
    ofHostEntry hostEntry;
    try {
        hostEntry = DNS::hostByName(hostname);
    } catch(const HostNotFoundException& exc) {
        ofLogError("ofGetHostByName") << "Host not found: " << hostname;
        return hostEntry;
    } catch(const NoAddressFoundException& exc) {
        ofLogError("ofGetHostByName") << "No Address found: " << hostname;
        return hostEntry;
    } catch(const DNSException& exc) {
        ofLogError("ofGetHostByName") << "DNS Exception: " << hostname;
        return hostEntry;
    } catch(const IOException& exc) {
        ofLogError("ofGetHostByName") << "IO Exception: " << hostname;
        return hostEntry;
    } catch(...) {
        ofLogError("ofGetHostByName") << "Unknown Exception: " << hostname;
        return hostEntry;
    }
    
    return hostEntry;
}

//------------------------------------------------------------------------------
ofHostEntry ofGetHostByAddress(const ofIPAddress& ipAddress) {
    ofHostEntry hostEntry;
    try {
        hostEntry = DNS::hostByAddress(ipAddress);
    } catch(const HostNotFoundException& exc) {
        ofLogError("ofGetHostByAddress") << "Host not found: " << ipAddress.toString();
        return hostEntry;
    } catch(const DNSException& exc) {
        ofLogError("ofGetHostByAddress") << "DNS Exception: " << ipAddress.toString();
        return hostEntry;
    } catch(const IOException& exc) {
        ofLogError("ofGetHostByAddress") << "IO Exception: " << ipAddress.toString();
        return hostEntry;
    } catch(...) {
        ofLogError("ofGetHostByAddress") << "Unknown Exception: " << ipAddress.toString();
        return hostEntry;
    }
    
    return hostEntry;
}

//------------------------------------------------------------------------------
ofHostEntry ofGetHost(const string& address) {
    ofHostEntry hostEntry;
    try {
        hostEntry = DNS::resolve(address);
    } catch(const HostNotFoundException& exc) {
        ofLogError("ofGetHost") << "Host not found: " << address;
        return hostEntry;
    } catch(const DNSException& exc) {
        ofLogError("ofGetHost") << "DNS Exception: " << address;
        return hostEntry;
    } catch(const IOException& exc) {
        ofLogError("ofGetHost") << "IO Exception: " << address;
        return hostEntry;
    } catch(...) {
        ofLogError("ofGetHost") << "Unknown Exception: " << address;
        return hostEntry;
    }
    
    return hostEntry;
}

//------------------------------------------------------------------------------
ofHostEntry ofGetThisHost() {
    ofHostEntry hostEntry;
    try {
        hostEntry = DNS::thisHost();
    } catch(const HostNotFoundException& exc) {
        ofLogError("ofGetThisHost") << "Host not found.";
        return hostEntry;
    } catch(const NoAddressFoundException& exc) {
        ofLogError("ofGetThisHost") << "No Address found.";
        return hostEntry;
    } catch(const DNSException& exc) {
        ofLogError("ofGetThisHost") << "DNS Exception.";
        return hostEntry;
    } catch(const IOException& exc) {
        ofLogError("ofGetThisHost") << "IO Exception.";
        return hostEntry;
    } catch(...) {
        ofLogError("ofGetThisHost") << "Unknown Exception.";
        return hostEntry;
    }
    
    return hostEntry;
}
