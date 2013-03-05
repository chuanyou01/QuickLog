#ifndef HTTPPROTOCOL_URL_H_
#define HTTPPROTOCOL_URL_H_
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Url
{
public:
	Url(void);
	~Url(void);

	typedef enum {
		url_XAlphas		= (1<<0),
		url_XPAlphas	= (1<<1),
		url_Path		= (1<<2)
	} nsEscapeMask;


	static std::string EncodeUrl(const char *url,int mask,bool bCovertToUtf8=false);
	static int EncodeUrl(const char *str,char *outbuf,int &outbuflen,int mask);
	static std::string DecodeUrl(const char *url,bool bCovertUtf8=false);
	static int DecodeUrl(const char *str,char *outbuf,int &outbuflen);


	bool ParseUrl(std::string strUrl,bool isDecode=true);
	bool MakeUrl();
	std::string GetUrlType();

	std::string GetScheme(){ return m_scheme; };
	std::string GetHost(){ return m_host; }
	std::string GetUser(){ return m_user; }
	std::string GetPass(){ return m_pass; }
	std::string GetPath(){ return m_path; }
	std::string GetQuery(){ return m_query; }
	std::string GetFragment(){ return m_fragment; }

	bool GetQueryStringMap(std::map<std::string,std::string > &smap);
	static bool CovertPostStringToMap(std::string strPost,std::map<std::string,std::string > &smap);
	

	void SetScheme(std::string scheme){ m_scheme=scheme; };
	void SetHost(std::string host){ m_host=host; };
	void SetUser(std::string user){ m_user=user; };
	void SetPass(std::string pass){ m_pass=pass; };
	void SetPath(std::string path){ m_path=path; };
	void SetQuery(std::string query){ m_query=query; };
	void SetFragment(std::string fragment){ m_fragment=fragment; };

protected:
	void InitData();
	bool ParseUri(std::string strUri);

protected:

	string m_scheme;
	string m_host;
	string m_user;
	string m_pass;
	string m_path;
	string m_query;
	string m_fragment;

};

#endif
