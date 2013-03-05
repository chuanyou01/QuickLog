//#pragma once

#ifndef LIBCHEN_STRKEY_H_
#define LIBCHEN_STRKEY_H_

#include <string>
#include "chentype.h"


namespace chen{
	class word{
	public:
		word(){m_word=S_STRDUP("");}
		word(const char* wd);
		word(const word& wd);
		word(const std::string &str);
		virtual ~word()
		{
			if(m_word)
				free(m_word);
		}

		word& operator=(const word& wd);

		word& operator=(const char *p);

		bool operator==(const word &wd) const;
		bool operator<(const word &wd) const;

		bool operator>(const word &wd) const;


		bool operator>=(const word &wd) const;
		bool operator<=(const word &wd) const;

		const char *getword(void) const ;
		operator char*() const;
		operator const char *() const;
		bool empty();

	private:
		char *m_word;
	};
}

#endif
