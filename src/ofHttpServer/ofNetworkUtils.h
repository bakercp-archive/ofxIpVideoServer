/*==============================================================================
 
 Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#pragma once

#include <string>

#include "Poco/Environment.h"
#include "Poco/Exception.h"
#include "Poco/Net/DNS.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/NetException.h"

#include "Poco/Net/IPAddress.h"

#include "ofLog.h"

using std::string;

using Poco::Environment;
using Poco::SystemException;
using Poco::IOException;
using Poco::Net::DNS;
using Poco::Net::HostEntry;
using Poco::Net::IPAddress;
using Poco::Net::DNSException;
using Poco::Net::HostNotFoundException;
using Poco::Net::NoAddressFoundException;

typedef IPAddress ofIPAddress;
typedef HostEntry ofHostEntry;

//------------------------------------------------------------------------------
string ofGetHostName();

string ofGetMacAddress();

ofHostEntry ofGetHostByName(const string& hostname);
ofHostEntry ofGetHostByAddress(const ofIPAddress& ipAddress);

ofHostEntry ofGetHost(const string& address);

ofHostEntry ofGetHostInfo();

