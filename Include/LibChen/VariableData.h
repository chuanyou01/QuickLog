#ifndef LIBCHEN_VARIABLEDATA_H_
#define LIBCHEN_VARIABLEDATA_H_

#include <ctime>

namespace chen{

	class VariableData
	{
	public:

#define VDT_EMPTY			0x00
#define VDT_STR				0x01
#define VDT_I16				0x02
#define VDT_I32				0x03
#define VDT_I64				0x04
#define VDT_I8				0x05
#define VDT_DOUBLE			0x06
#define VDT_FLOAT			0x07
#define VDT_BIN				0x08
#define VDT_TIME			0x09
		VariableData(void);
		~VariableData(void);

		VariableData(int data);
		VariableData(short data);
		VariableData(__int64 data);
		VariableData(const char *str);
		VariableData(double	data);
		VariableData(float data);
		VariableData(char *data,int len);
		VariableData(char *data);
		VariableData(const VariableData& vd);

		void Clear();

		VariableData& operator=(int data);
		VariableData& operator=(short data);
		VariableData& operator=(float data);
		VariableData& operator=(double data);
		VariableData& operator=(__int64 data);
		VariableData& operator=(const char *str);
		VariableData& operator=(unsigned char data);
		VariableData& operator=(const VariableData& vd);

#define RV_COMPARE_TRUE		1
#define RV_COMPARE_FALSE	0
#define RV_COMPARE_ERROR	-1

		bool operator<(const VariableData &vd) const;
		bool operator>(const VariableData &vd) const;
		bool operator==(const VariableData &vd) const;
		bool operator<=(const VariableData &vd) const;
		bool operator>=(const VariableData &vd) const;
		bool operator!=(const VariableData &vd) const;

		operator int() const;
		operator short() const;
		operator __int64() const;
		operator unsigned char() const;
		operator double() const;
		operator float() const;
		operator char*() const;

		bool PutBinData(const char *data,int len,bool isAllocMem=true);
		bool GetBinData(char *buf,int&len);
		bool PutTimeValue(time_t ttm);
		bool GetTimeValue(time_t &ttm) const;

		char * SerialData(char *data,int *len) const;
		bool UnSerial(const char *data,int len);
		int Size(void) const;


	public:
		int m_dt;
		union{
			int				i32;
			__int64			i64;
			short			i16;
			unsigned char	i8;
			double			df;
			float			f;
			char			*str;
			time_t			stm;
		} m_data;
		struct st_bin
		{
			unsigned char *bin;
			int	len;
		} m_bin;

	protected:
		void Init();
		bool m_isAllocMemory;


	};
}

#endif
