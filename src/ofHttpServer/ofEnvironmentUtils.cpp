#include "ofEnvironmentUtils.h"

//------------------------------------------------------------------------------
string ofGetEnvironmentalVariable(const string& name, const string& defaultValue) {
    return Environment::get(name,defaultValue);
}

//------------------------------------------------------------------------------
bool ofHasEnvironmentalVariable(const string& name) {
    return Environment::has(name);
}

//------------------------------------------------------------------------------
void ofSetEnvironmentalVariable(const string& name, const string& value) {
    Environment::set(name,value);
}

//------------------------------------------------------------------------------
string ofGetOSName() {
    return Environment::osName();
}

//------------------------------------------------------------------------------
string ofGetOSVersion() {
    return Environment::osVersion();
}

//------------------------------------------------------------------------------
string ofGetOSDisplayName() {
    return Environment::osDisplayName();
}

//------------------------------------------------------------------------------
string ofGetOSArchitecture() {
    return Environment::osArchitecture();
}

//------------------------------------------------------------------------------
unsigned int ofGetProcessorsCount() {
    return Environment::processorCount();
}