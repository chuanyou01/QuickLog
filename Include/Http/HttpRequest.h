#ifndef HTTPPROTOCOL_HTTPREQUEST_H_
#define HTTPPROTOCOL_HTTPREQUEST_H_

#include <LibChen/Socket.h>
#include <LibChen/Buffer.h>
#include "HttpHead.h"

#define HP_HR_OK						1
#define HP_HR_FAILED					0
#define HP_HR_TIMEOUT					-5
#define HP_HR_INVAILDURL				-6
#define HP_HR_ALLOCMEMORYFAILED			-7
#define HP_HR_CREATEHEADERFAILED		-8
#define HP_HR_CONNECTSERVERFAILED		-9
#define HP_HR_COMMUNICATIONFAILED		-10
#define HP_HR_SOCKETTIMEOUT				-11
#define HP_HR_SOCKETERROR				-12
#define HP_HR_RECVRESPONSEHEADERFAILED	-13
#define HP_HR_RESPONSEFORMATERROR		-14
#define HP_HR_BADRESPONSEHEADER			-15
#define HP_HR_OVERMAXREDIRECT			-16
#define HP_HR_UNKNOWNCONTENTENCODING	-17


class HttpRequest
{
public:
	HttpRequest(void);
	~HttpRequest(void);

	void SetUrl(const char *url);
	int SendRequest();
	int SendRequest(const char *url);
	int SendRequest(const char *url,const char *addData,int len,bool isPost);
	int SendRequest(const char *addData,int len,bool isPost);
	void SetUri(const char *uri);
	void SetServerPort(unsigned short nPort);
	void SetServer(const char *serverAddress,unsigned short nPort=80);
	int RecvResponse();
	int CheckResponseBody(bool &HasBody,int &nBodyLen);
	int GetResponseStatus();
	int RecvResponseBody();
	int GetRecvBodyLen(){ return m_recvLen; }
    char *GetRecvData(int &len);
	static bool ParseRequestUrl(std::string Url,std::string &Host,unsigned short &Port,std::string &uri);
	static int ParseChunkedCode(chen::TCPStream &ts,chen::buffer &buf,std::list<std::string > &trailers,int timeout);

	void Reset();
	
	
public:

	bool ParseUrl();

	HttpRequestHead m_requestHead;
	HttpResponseHead m_responseHead;

	int m_timeOut;
	bool m_autoRedirect;
	int m_maxRedirect;
	bool m_allowRetry;

protected:

	int SendRawRequest(const char *data,int len);
	int RecvRawResponse(int index=0);
	int RecvRawResponseBody();

	void InitData();


	chen::TCPStream m_ts;
	chen::buffer m_buffer;
	int m_recvLen;
	std::string m_url;
	std::string m_uri;
	unsigned short m_nPort;
	std::string m_serverAddress;
//	const char *m_postData;




};

#endif
