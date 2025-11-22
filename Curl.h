
#pragma once


#include <curl/curl.h>

#include "CurlRequest.h"
#include "Settings.h"


class Curl
{
public:

	static Curl& Instance() {
		static Curl instance;
		return instance;
	}

public:

    CurlRequest newRequest( const std::string& url ) {
        CurlRequest request( url );
        request.settings() = mSettings;

        return request;
    }

    Settings& settings() {
        return mSettings;
    }

private:

    Curl() {
        curl_global_init( CURL_GLOBAL_ALL );
    }

    ~Curl() {
        curl_global_cleanup();
    }

private:

    Settings mSettings;
};
