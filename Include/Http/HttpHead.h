#ifndef HTTPPROTOCOL_HTTPHEAD_H_
#define HTTPPROTOCOL_HTTPHEAD_H_
#include <iostream>
#include <string>
#include <LibChen/TimeFace.h>
#include <LibChen/buffer.h>
#include <list>
#include <map>

using namespace std;

#define HRH_ERROR_OK							1
#define HRH_ERROR_FAILED						0
#define HRH_ERROR_INVALIDREQUESTTYPE			10
#define HRH_ERROR_UNKNOWNREQUESTTYPE			11
#define HRH_ERROR_BUFFERTOOSMALL				12

#define HRH_ERROR_HEADERFORMAT					20
#define HRH_ERROR_VALUEEMPTY					21
#define HRH_ERROR_UNKNOWNFIELD					22

#define HT_ERROR_PARSEFORMAT					110



struct st_content_range
{
#define HT_CR_SUFFIX		-1
	int nBegin;
	int nEnd;
};

typedef std::list<struct st_content_range >	CTRANGELIST;

class HttpAssistant
{
public:
	HttpAssistant();
	~HttpAssistant();

	static int ParseRangesSpecifier(std::string str,std::string &unit,CTRANGELIST &ctlist);
#define HT_CONTENTSIZE_UNKNOWN			-1
	static std::string MakeContentRangeSpec(std::string unit,struct st_content_range &range,int total);
	static std::string MakeContentRangeSpec(std::string unit,int nbegin,int nend,int total);

};

class Http
{
public:
	Http();
	~Http();

	enum Type{ 
		ht_unknown=0,
		ht_get=1,
		ht_post=2,
		ht_options=3,
		ht_head=4,
		ht_put=5,
		ht_delete=6,
		ht_trace=7
	};

	enum PVersion{
		hvt_10=1,
		hvt_11=2,
		hvt_09=3
	};
	enum connection
	{
		keep_alive=1,
		close=2
	};
	enum pragma
	{
		pragma_unknown=0,
		no_cache=1
	};
	enum respone_status
	{
		st_100_continue=100,
		st_101_switch_protocols=101,
		st_200_ok=200,
		st_201_created=201,
		st_202_accepted=202,
		st_203_non_authoritative_information=203,
		st_204_no_content=204,
		st_205_reset_content=205,
		st_206_partial_content=206,
		st_300_multiple_choices=300,
		st_301_moved_permanently=301,
		st_302_found=302,
		st_303_see_other=303,
		st_304_not_modified=304,
		st_305_use_porxy=305,
		st_306_unused=306,
		st_307_temp_redirct=307,
		st_400_bad_request=400,
		st_401_unauthorized=401,
		st_403_forbidden=403,
		st_404_not_found=404,
		st_405_mothed_not_allowed=405,
		st_406_not_accepttable=406,
		st_407_proxy_authentication_required=407,
		st_408_request_timeout=408,
		st_409_conflict=409,
		st_410_gone=410,
		st_411_length_required=411,
		st_412_precondition_failed=412,
		st_413_request_entity_too_large=413,
		st_414_request_uri_too_long=414,
		st_415_unsupported_media_type=415,
		st_416_requested_range_not_satisfiable=416,
		st_417_expectation_failed=417,
		st_500_internal_server_error=500,
		st_501_not_implemented=501,
		st_502_bad_getway=502,
		st_503_service_unavailable=503,
		st_504_getway_timeout=504,
		st_505_http_version_not_supported=505

	};
	enum content_encoding
	{
		ce_identity=0,
		ce_gzip=1,
		ce_compress=2,
		ce_deflate=3,
		ce_unknown=6
	};

	int GetHttpVersion(){ return m_version; };
	int GetContentLength() { return m_content_length; }
	int GetTransferLength() { return m_transfer_length; }
	std::string GetRange() { return m_range; };
	std::string GetLastModified(){ return m_last_modified; };
	int GetContentEncoding() { return m_content_encoding; };
	std::string GetContentMD5() { return m_content_md5; };
	std::string GetContentLanguage() { return m_content_language; };
	std::string GetDate(){ return m_date; };
	int GetConnection() { return m_connection; }
	string GetVia(){ return m_via; };
	std::string GetTransferEncoding(){ return m_transfer_encoding;};
	int GetPragma(){ return m_pragma; };
	string GetKeepAlive() { return m_keep_alive; };
	string GetCacheControl(){ return m_cache_control; };
	string GetContentType() { return m_content_type; };
	string GetContentDispostion() { return m_content_disposition; };

	std::string GetAddHead(const std::string &name){ 
		std::map<std::string , std::string >::iterator it=m_common_heads.find(name);
		if(it!=m_common_heads.end())
			return (*it).second;
		else
			return "";

	}




	 ///////////////////////////////////////

	void SetHttpVersion(int version) { m_version=version; };
	void SetContentLength(int length) { m_content_length=length; };
	void SetTransferLength(int length) { m_transfer_length=length; };
	void SetRange(std::string range){ m_range=range; };
	void SetLastModified(std::string last_modified) { m_last_modified=last_modified; };
	void SetContentEncoding(int content_encoding) { m_content_encoding=content_encoding; }
	void SetContentMD5(std::string content_md5) { m_content_md5=content_md5; };
	void SetContentLanguage(std::string content_language) { m_content_language=content_language; };
	void SetDate(std::string date) { m_date=date; };
	void SetConnection(int connection) { m_connection=connection; };
	void SetVia(string via) { m_via=via; };
	void SetTransferEncoding(string transfer_encoding) { m_transfer_encoding=transfer_encoding; };
	void SetPragma(int pragma) { m_pragma=pragma; };
	void SetKeepAlive(string keep_alive){ m_keep_alive=keep_alive; };
	void SetCacheControl(string cache_control) { m_cache_control=cache_control; };
	void SetContentType(string content_type) { m_content_type=content_type; }
	void SetContentDisposition(string content_disposition) { m_content_disposition=content_disposition; }

	void SetAddHead(string name,string value) { if(!name.empty()) m_common_heads[name]=value; }



	/////////////////////////////////
	void SetTransferEncoding_Chunked() { return SetTransferEncoding("chunked"); }

	/////////////////////////////
	





	bool isChunkedEncoding();




protected:

	void BaseInitData();
	string Trim(string line);
	string get_content_encoding();
	string get_http_version();
	string get_connection();
	int covert_content_encoding(std::string str);
	int covert_connection(std::string str);
	string get_pragma();
	int covert_pragma(std::string str);

	void Clear();


protected:
	int m_version;
	int m_content_length;
	int m_transfer_length;
	std::string m_range;
	std::string m_last_modified;
	int m_content_encoding;
	std::string m_content_md5;
	std::string m_content_language;
	std::string m_date;
	int m_connection;
	string m_via;
	std::string m_transfer_encoding;
	int m_pragma;
	string m_keep_alive;
	string m_cache_control;
	string m_content_type;
	string m_content_disposition;

	std::map<std::string , std::string > m_common_heads;



};

class HttpRequestHead : public Http
{
public:
	HttpRequestHead(void);
	~HttpRequestHead(void);



	int ParseHeader(std::string first_line,std::list<std::string > & request_headers);
	int ParseHeader(std::list<std::string > &request_headers);
	int MakeHeader(char *pbuf,int &len);

	void Clear();

	void VisitAll();

	int GetRequestType(){ return m_request_type; };
	
	string GetRequestURI() { return m_uri; };
	string GetHost() { return m_host; };
	string GetAcceptLanguage() { return m_accept_language; };
	string GetUserAgent() { return m_user_agent; };
	string GetAcceptEncoding(){ return m_accept_encoding; };
	string GetAccept() { return m_accept; };
	std::string GetIfModifiedSince(){ return m_if_modified_since; };
	std::string GetAcceptCharset(){ return m_accept_charset;};
	std::string GetTE(){return m_te; };
	std::string GetReferer() { return m_referer; };
	std::string GetCookie() {return m_cookie; };
	std::string GetIfRange(){ return m_if_range; };
	std::string GetIfMatch(){ return m_if_match; };
	std::string GetIfMatchAny() { return m_if_match_any; };
	std::string GetNoneMatch() { return m_if_none_match; };
	std::string GetIfNoneMatchAny() { return m_if_none_match_any; };
	std::string GetIfUnmodifiedSince(){ return m_if_unmodified_since; };
	std::string GetUACPU(){ return m_ua_cpu; };



	////////////////////set//////////////////

	void SetRequestType(int type){ m_request_type=type; };
	void SetRequestURI(std::string uri) { m_uri=uri; };
	void SetHost(std::string host) { m_host=host; };
	void SetAcceptLanguage(std::string language) { m_accept_language=language; };
	void SetUserAgent(std::string user_agent){ m_user_agent=user_agent; };
	void SetAcceptEncoding(string accept_encoding) { m_accept_encoding=accept_encoding; };
	void SetAccept(std::string accept) { m_accept=accept; };
	void SetIfModifiedSince(std::string if_modified_since) { m_if_modified_since=if_modified_since;};
	void SetAcceptCharset(std::string accept_charset) { m_accept_charset=accept_charset;};

	void SetReferer(std::string referer) { m_referer=referer;};
	void SetCookie(std::string cookie) { m_cookie=cookie; };
	void SetIfRange(std::string if_range){ m_if_range=if_range; };
	void SetIfMatch(std::string if_match) { m_if_match=if_match; };
	void SetIfMatchAny(std::string if_match_any) { m_if_match_any=if_match_any; };
	void SetIfNoneMatch(std::string if_none_match) { m_if_none_match=if_none_match; };
	void SetIfNoneMatchAny(std::string if_none_match_any) { m_if_none_match_any=if_none_match_any; };
	void SetIfUnmodifiedSince(std::string if_unmodified_since) { m_if_unmodified_since=if_unmodified_since; }
	void SetTE(std::string te) { m_te=te; };
	void SetUACPU(std::string ua_cpu) { m_ua_cpu=ua_cpu; };

	void SetAuthorization(std::string uid,std::string pwd){ m_uid=uid;m_pwd=pwd; };

protected:
	void InitData();
	string get_http_requesttype();

	int ParseFirstLine(std::string sLine);
	int ParseHeaderLine(std::string sLine);
protected:
	int m_request_type;
	string m_uri;
	string m_host;
	string m_accept_language;
	string m_user_agent;
	string m_accept_encoding;
	string m_accept;
	string m_accept_charset;
	//int m_range_begin;
	//int m_range_end;
	std::string  m_if_modified_since;
	//std::string m_transfer_encoding;
	std::string m_referer;
	std::string m_cookie;
	std::string m_if_range;
	std::string m_if_match;
	std::string m_if_match_any;
	std::string m_if_none_match;
	std::string m_if_none_match_any;
	std::string m_if_unmodified_since;
	std::string m_te;
	std::string m_ua_cpu;

	std::string m_uid;
	std::string m_pwd;


};

class HttpResponseHead : public Http
{
public:
	HttpResponseHead();
	~HttpResponseHead();

	int ParseHeader(std::string status_line,std::list<std::string > &response_headers);
	int ParseHeader(std::list<std::string > &response_headers);
	int MakeHeader(char *pbuf,int &len);
	void Clear();

	void VisitAll();

	int GetStatus(){ return m_status; };
//	string GetContentType() { return m_content_type; };
	string GetServer() { return m_server; };
	string GetEtag() { return m_etag; };
	string GetWWWAuthenticate() { return m_www_authenticate; };
	string GetAllow(){ return m_allow; };
	string GetContentRange() { return m_content_range; };
	string GetExpires() { return m_expires; };
	string GetAge() { return m_age; };

	string GetSetCookie(){ return m_set_cookie; };
	string GetStatusDescription() { return m_status_description; };
	string GetContentLocation(){ return m_content_location; };
	string GetAcceptRanges(){ return m_accept_ranges; };
	string GetXPoweredBy(){ return m_x_powered_by; };
	string GetVary(){ return m_vary; };
	string GetXCache(){ return m_x_cache; };
	string GetMimeVersion(){ return m_mime_version; }
	string GetLocation(){ return m_location; };
	string GetMaxAge(){ return m_max_age; };


	std::string GetContentCharset();



	////////////////////////////////////set//////////////

	void SetStatus(int status) { m_status=status; }
//	void SetContentType(string content_type) { m_content_type=content_type; }
	void SetServer(string server) { m_server=server; }
	void SetEtag(string etag){ m_etag=etag; }
	void SetWWWAuthenticate(string www_authenticate) { m_www_authenticate=www_authenticate; }
	void SetAllow(string allow){ m_allow=allow; };
	void SetContentRange(string content_range) { m_content_range=content_range; }
	void SetExpires(string expires) { m_expires=expires; }
	void SetAge(string age){ m_age=age; }
	
	void SetSetCookie(string set_cookie) { m_set_cookie=set_cookie; };
	void SetStatusDescription(string status_des) { m_status_description=status_des; };
	void SetContentLocation(string content_location) { m_content_location=content_location; };
	void SetAcceptRanges(string accept_ranges) { m_accept_ranges=accept_ranges; };
	void SetXPoweredBy(string x_powered_by) { m_x_powered_by=x_powered_by;}
	void SetVary(string vary){ m_vary=vary; }
	void SetXCache(string x_cache) { m_x_cache=x_cache; };
	void SetMimeVersion(string mime_version){ m_mime_version=mime_version; };
	void SetLocation(string location) { m_location=location; };
	void SetMaxAge(string max_age) { m_max_age=max_age; };




protected:
	void InitData();
	int ParseStatusLine(std::string sLine);
	int ParseHeaderLine(std::string sLine);

protected:
	int m_status;
	string m_status_description;
//	string m_content_type;
	string m_server;
	string m_etag;
	string m_www_authenticate;
	string m_allow;
	string m_content_range;
	string m_expires;
	string m_age;

	string m_set_cookie;
	string m_content_location;
	string m_accept_ranges;
	string m_x_powered_by;
	string m_vary;
	string m_x_cache;
	string m_location;
	string m_mime_version;
	string m_max_age;


};

#endif
