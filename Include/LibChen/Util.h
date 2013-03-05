#ifndef LIBCHEN_UTIL_H_
#define LIBCHEN_UTIL_H_

#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace chen{

	class Util
	{
	public:
		Util(void);
		~Util(void);

		static bool ParseFlagString(std::string str,std::string sFlag,std::list<std::string> &slist);
		static std::string ReplaceString(std::string rawString ,std::string rStr,std::string oStr);
		static unsigned int CheckSum(const char *pBuf,int dlen);
		static int str_nocase_cmp(const char *sr,const char *so);
		static int str_nocase_find(const char *sr,const char *so);

		static bool Utf8TOString(const char *pdata,int dlen,std::string &strRet);
		static bool StringTOUtf8(string str,char *pdata,int &dlen);

	};
}

#endif
