#ifndef LIBCHEN_EXCEPTION_H_
#define LIBCHEN_EXCEPTION_H_

#include <string.h>

namespace chen{

	class exception
	{
	public:
		enum { dlen=256, tlen=20 };
		char ErrorType[tlen];
		char Description[dlen];
		exception(const char * e=NULL, const char* t="Exception") throw()
		{
			ErrorType[0]='\0';
			Description[0]='\0';
			if((e!=NULL)&&(strlen(e)<dlen))
				//strcpy(Description,e);
				strcpy_s (Description, sizeof(Description), e);
			else
				//strcpy(Description,"Exception");
				strcpy_s(Description, sizeof(Description), _T("Exception"));

			if(strlen(t)<tlen)
				//strcpy(ErrorType,t);
				strcpy_s(ErrorType, sizeof(ErrorType), t);
			else
				//strcpy(ErrorType,"MSException");
				strcpy_s(ErrorType, sizeof(ErrorType), _T("MSException"));

		}

		virtual const char* GetErrorType() const throw() { return ErrorType;}
		virtual const char* GetDescription() const throw() { return Description;}
		virtual ~exception(){;};

	};
}

#endif
