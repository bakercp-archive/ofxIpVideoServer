#pragma once

#include <string>
#include <vector>

#include "Poco/URI.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Net/NameValueCollection.h"

#include "ofUtils.h"

using std::string;
using std::vector;

using Poco::StringTokenizer;
using Poco::URI;
using Poco::Net::NameValueCollection;

NameValueCollection ofGetQueryMap(const URI& uri);