
SET(SOURCES
	CurlRequest.cpp
)

SET(HEADERS
	Curl.h
	CurlRequest.h
    Settings.h
)

SET(DEPENDENCIES
)

SET(MODULES
    curl
)

build_static_lib( curlcpp "" )
