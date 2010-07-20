#ifndef HTTP_CONSTS_H
#define HTTP_CONSTS_H

#define HTTP_CS_CR						"\015"
#define HTTP_CS_LF						"\012"
#define HTTP_CS_CRLF					HTTP_CS_CR HTTP_CS_LF

#define HTTP_HEADER_ACCEPT				"Accept"
#define HTTP_HEADER_ACCEPT_CHARSET		"Accept-Charset"
#define HTTP_HEADER_ACCEPT_ENCODING		"Accept-Encoding"
#define HTTP_HEADER_ACCEPT_LANGUAGE		"Accept-Language"
#define HTTP_HEADER_ACCEPT_RANGES		"Accept-Ranges"
#define HTTP_HEADER_AGE					"Age"
#define HTTP_HEADER_ALLOW				"Allow"
#define HTTP_HEADER_AUTHORIZATION		"Authorization"
#define HTTP_HEADER_CACHE_CONTROL		"Cache-Control"
#define HTTP_HEADER_CONNECTION			"Connection"
#define HTTP_HEADER_CONTENT_ENCODING	"Content-Encoding"
#define HTTP_HEADER_CONTENT_LANGUAGE	"Content-Language"
#define HTTP_HEADER_CONTENT_LENGTH		"Content-Length"
#define HTTP_HEADER_CONTENT_LOCATION	"Content-Location"
#define HTTP_HEADER_CONTENT_MD5			"Content-MD5"
#define HTTP_HEADER_CONTENT_RANGE		"Content-Range"
#define HTTP_HEADER_CONTENT_TYPE		"Content-Type"
#define HTTP_HEADER_DATE				"Date"
#define HTTP_HEADER_ETAG				"Etag"
#define HTTP_HEADER_EXPECT				"Expect"
#define HTTP_HEADER_EXPIRES				"Expires"
#define HTTP_HEADER_FROM				"From"
#define HTTP_HEADER_HOST				"Host"
#define HTTP_HEADER_IF_MATCH			"If-Match"
#define HTTP_HEADER_IF_MODIFIED_SINCE	"If-Modified-Since"
#define HTTP_HEADER_IF_NONE_MATCH		"If-None-Match"
#define HTTP_HEADER_IF_RANGE			"If-Range"
#define HTTP_HEADER_IF_UNMODIFIED_SINCE	"If-Unmodified-Since"
#define HTTP_HEADER_LAST_MODIFIED		"Last-Modified"
#define HTTP_HEADER_LOCATION			"Location"
#define HTTP_HEADER_MAX_FORWARDS		"Max-Forwards"
#define HTTP_HEADER_PRAGMA				"Pragma"
#define HTTP_HEADER_PROXY_AUTHENITCATE	"Proxy-Authenticate"
#define HTTP_HEADER_PROXY_AUTHORIZATION	"Proxy-Authorization"
#define HTTP_HEADER_RANGE				"Range"
#define HTTP_HEADER_REFERER				"Referer"
#define HTTP_HEADER_RETRY_AFTER			"Retry-After"
#define HTTP_HEADER_SERVER				"Server"
#define HTTP_HEADER_TE					"TE"
#define HTTP_HEADER_TRAILER				"Trailer"
#define HTTP_HEADER_TRANSFER_ENCODING	"Transfer-Encoding"
#define HTTP_HEADER_UPGRADE				"Upgrade"
#define HTTP_HEADER_USER_AGENT			"User-Agent"
#define HTTP_HEADER_VARY				"Vary"
#define HTTP_HEADER_VIA					"Via"
#define HTTP_HEADER_WARNING				"Warning"
#define HTTP_HEADER_WWW_AUTHENTICATE	"WWW-Authenticate"

#define HTTP_CONNECTION_CLOSE			"close"

#define HTTP_STATUS_CODE_OK						200
#define HTTP_STATUS_CODE_NOT_FOUND				404
#define HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR	500

#endif
