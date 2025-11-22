
#include "CurlRequest.h"


size_t write_data( void *contents, size_t size, size_t nmemb, void *stream )
{
	static_cast<std::string*>( stream )->append( static_cast<char*>( contents ), size * nmemb );

	return size * nmemb;
}


CurlRequest::CurlRequest( const std::string& url )
{
    mURL = url;

    curl_easy_setopt( mRequest.Handle, CURLOPT_WRITEFUNCTION, write_data );
}

CurlRequest::~CurlRequest()
{
    curl_easy_cleanup( mRequest.Handle );
}

std::string CurlRequest::execute( const std::string& url )
{
    if ( mSettings.UseAuthentication ) {
        curl_easy_setopt( mRequest.Handle, CURLOPT_PASSWORD, mSettings.Password.c_str() );
        curl_easy_setopt( mRequest.Handle, CURLOPT_USERNAME, mSettings.Username.c_str() );
    }

    curl_easy_setopt( mRequest.Handle, CURLOPT_NOPROGRESS, !mSettings.ShowProgress );
    curl_easy_setopt( mRequest.Handle, CURLOPT_URL, url.empty() ? mURL.c_str() : url.c_str() );
    curl_easy_setopt( mRequest.Handle, CURLOPT_VERBOSE, mSettings.VerboseOutput );
    curl_easy_setopt( mRequest.Handle, CURLOPT_WRITEDATA, mSettings.VerboseOutput );

    curl_easy_setopt( mRequest.Handle, CURLOPT_HTTPHEADER, mRequest.HeaderList );
    curl_easy_setopt( mRequest.Handle, CURLOPT_WRITEDATA, &mRequest.Result );

    mLastError = curl_easy_perform( mRequest.Handle );

    if ( mLastError ) {
        return "";
    }

    return std::string( mRequest.Result );
}

int32_t CurlRequest::lastError() const
{
    return mLastError;
}

void CurlRequest::setBearer( const std::string& bearer )
{
    curl_easy_setopt( mRequest.Handle, CURLOPT_XOAUTH2_BEARER, bearer.c_str() );
}

void CurlRequest::setData( const std::string& data )
{
    curl_easy_setopt( mRequest.Handle, CURLOPT_POST, 1L );
    // size of the data to copy from the buffer and send in the request
    curl_easy_setopt( mRequest.Handle, CURLOPT_POSTFIELDSIZE, static_cast<long>( data.size() ) );
    // send data from the local stack
    curl_easy_setopt( mRequest.Handle, CURLOPT_COPYPOSTFIELDS, data.c_str() );
}

void CurlRequest::setHeader( const std::string& header )
{
    mRequest.HeaderList = curl_slist_append( mRequest.HeaderList, header.c_str() );
}

void CurlRequest::setOption( int32_t option, int32_t value )
{
    curl_easy_setopt( mRequest.Handle, static_cast<CURLoption>( option ), value );
}

void CurlRequest::setOption( int32_t option, const std::string& value )
{
    curl_easy_setopt( mRequest.Handle, static_cast<CURLoption>( option ), value.c_str() );
}
