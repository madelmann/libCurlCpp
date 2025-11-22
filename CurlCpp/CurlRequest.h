
#pragma once

#include <string>
#include <curl/curl.h>

#include "Settings.h"


class CurlRequest
{
public:

    CurlRequest( const std::string& url = "" );
    ~CurlRequest();

public:

    std::string execute( const std::string& url = "" );

    int32_t lastError() const;

    void setBearer( const std::string& bearer );
    void setData( const std::string& data );
    void setHeader( const std::string& header );
    void setOption( int32_t option, int32_t value );
    void setOption( int32_t option, const std::string& value );

    Settings& settings() {
        return mSettings;
    }

private:

    struct Request_t
    {
        CURL*		Handle { nullptr };
        std::string	Header;
        struct curl_slist* HeaderList { nullptr };
        std::string	Result;

        Request_t() {
            Handle = curl_easy_init();
        }
        ~Request_t() {
            curl_slist_free_all( HeaderList );

            curl_easy_cleanup( Handle );
        }
    };

private:

    int32_t mLastError;
    Request_t mRequest;
    Settings mSettings;
    std::string mURL;
};

