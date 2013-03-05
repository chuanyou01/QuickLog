#ifndef LIBCHEN_BYTEORDER_H_
#define LIBCHEN_BYTEORDER_H_

namespace chen
{

	class ByteOrder
	{
	public:
		ByteOrder(void);
		~ByteOrder(void);

		static bool isBigEndian();
	};

#if !defined (WIN32) || defined(_CHEN_BYTEORDER_BIGENDIAN_)

#define bo_int2buf(i,p)	{	\
	*(unsigned char*)p=(unsigned char)(i);	\
	*((unsigned char*)p+1)=(unsigned char)((i) >> 8);	\
}

#define bo_int3buf(i,p) {	\
	*(unsigned char *)p=(unsigned char)i;	\
	*((unsigned char *)p+1)=(unsigned char)((i) >> 8);	\
	*((unsigned char *)p+2)=(unsigned char)((i) >> 16);	\
}

#define bo_int4buf(i,p) {	\
	do{	\
	*(unsigned char *)p=(unsigned char)(i);	\
	*((unsigned char *)p+1)=(unsigned char)((i) >> 8);	\
	*((unsigned char *)p+2)=(unsigned char)((i) >> 16);	\
	*((unsigned char *)p+3)=(unsigned char)((i) >> 24);	\
	}while(0);	\
}

#define bo_int8buf(i,p) {	\
	*(unsigned char *)p=(unsigned char)i;	\
	*((unsigned char *)p+1)=(unsigned char)((i) >> 8);	\
	*((unsigned char *)p+2)=(unsigned char)((i) >> 16);	\
	*((unsigned char *)p+3)=(unsigned char)((i) >> 24);	\
	*((unsigned char *)p+4)=(unsigned char)((i) >> 32);	\
	*((unsigned char *)p+5)=(unsigned char)((i) >> 40);	\
	*((unsigned char *)p+6)=(unsigned char)((i) >> 48);	\
	*((unsigned char *)p+7)=(unsigned char)((i) >> 56);	\
}





//#define bo_bufint2(i,p) {	\
//	do{		\
//	(unsigned short)i=0;	\
//	(unsigned short)temp_st=*(unsigned char *)p;	\
//	i|=temp_st;	\
//	temp_st=*((unsigned char *)p+1);	\
//	i|=(temp_st << 8);	\
//	}while(0);	\
//}

#define bo_bufint2(p)	\
	(short)(*(unsigned char *)p + ((short)(*((unsigned char *)p+1)) << 8));	

#define bo_bufuint2(p)	\
	(unsigned short)(*(unsigned char *)p + ((unsigned short)(*((unsigned char *)p+1)) << 8));	


#define bo_bufint3(p)	\
	(long)(*(unsigned char *)p +	\
	((long)(*((unsigned char *)p+1)) << 8 ) + \
	((long)(*((unsigned char *)p+2)) << 16 ));


#define bo_bufint4(p)	\
	(long)(*(unsigned char *)p +	\
	((long)(*((unsigned char *)p+1)) << 8 ) + \
	((long)(*((unsigned char *)p+2)) << 16 )+	\
	((long)(*((unsigned char *)p+3)) << 24 ));	


#define bo_bufuint4(p)	\
	(unsigned long)(*(unsigned char *)p +	\
	((unsigned long)(*((unsigned char *)p+1)) << 8 ) +	\
	((unsigned long)(*((unsigned char *)p+2)) << 16 )+	\
	((unsigned long)(*((unsigned char *)p+3)) << 24 ));

#define bo_bufint8(p) \
	(__int64)(*(unsigned char *)p +	\
	((__int64)(*((unsigned char *)p+1)) << 8 ) +	\
	((__int64)(*((unsigned char *)p+2)) << 16 )+	\
	((__int64)(*((unsigned char *)p+3)) << 24 )+	\
	((__int64)(*((unsigned char *)p+4)) << 32 )+	\
	((__int64)(*((unsigned char *)p+5)) << 40 )+	\
	((__int64)(*((unsigned char *)p+6)) << 48 )+	\
	((__int64)(*((unsigned char *)p+7)) << 56 ));	


#define bo_bufuint8(p) \
	(unsigned __int64)(*(unsigned char *)p +	\
	((unsigned __int64)(*((unsigned char *)p+1)) << 8 ) +	\
	((unsigned __int64)(*((unsigned char *)p+2)) << 16 )+	\
	((unsigned __int64)(*((unsigned char *)p+3)) << 24 )+	\
	((unsigned __int64)(*((unsigned char *)p+4)) << 32 )+	\
	((unsigned __int64)(*((unsigned char *)p+5)) << 40 )+	\
	((unsigned __int64)(*((unsigned char *)p+6)) << 48 )+	\
	((unsigned __int64)(*((unsigned char *)p+7)) << 56 ));	

#else

#define bo_int2buf(i,p)	memcpy((unsigned char *)p,(unsigned char *)(&i),2);
#define bo_int3buf(i,p) memcpy((unsigned char *)p,(unsigned char *)(&i),3);
#define bo_int4buf(i,p) memcpy((unsigned char *)p,(unsigned char *)(&i),4);
#define bo_int8buf(i,p) memcpy((unsigned char *)p,(unsigned char *)(&i),8);

#define bo_bufint2(p) (*((short *)(p)));
#define bo_bufuint2(p) (unsigned short)(*((unsigned short *)(p)));
#define bo_bufint3(p) (int)((unsigned int)(((unsigned char *)(p))[2]) << 16 |	\
	(unsigned int)(((unsigned char *)(p))[1]) << 8 |	\
	(unsigned int)(((unsigned char *)(p))[0]));
#define bo_bufint4(p) (*((int *)(p)));
#define bo_bufuint4(p) (unsigned int)(*((unsigned int *)(p)));
#define bo_bufint8(p) (*((__int64 *)(p)));
#define bo_bufuint8(p) (unsigned __int64)(*((unsigned __int64 *)(p)));


#endif





#ifdef CHEN_BYTEORDER_BIGENDIAN_

#define bo_float4buf(f,p){	\
	*(unsigned char *)p=((unsigned char *)&f)[3];	\
	*((unsigned char *)p+1)=((unsigned char *)&f)[2];	\
	*((unsigned char *)p+2)=((unsigned char *)&f)[1];	\
	*((unsigned char *)p+3)=((unsigned char *)&f)[0];	\
}

#define bo_float8buf(f,p){	\
	*(unsigned char *)p=((unsigned char *)&f)[7];	\
	*((unsigned char *)p+1)=((unsigned char *)&f)[6];	\
	*((unsigned char *)p+2)=((unsigned char *)&f)[5];	\
	*((unsigned char *)p+3)=((unsigned char *)&f)[4];	\
	*((unsigned char *)p+4)=((unsigned char *)&f)[3];	\
	*((unsigned char *)p+5)=((unsigned char *)&f)[2];	\
	*((unsigned char *)p+6)=((unsigned char *)&f)[1];	\
	*((unsigned char *)p+7)=((unsigned char *)&f)[0];	\
}

#define bo_buffloat8(f,p)
	do{	\
	double tem_d;	\
	((unsigned char *)&tem_d)[0]=((unsigned char *)p)[7];	\
	((unsigned char *)&tem_d)[1]=((unsigned char *)p)[6];	\
	((unsigned char *)&tem_d)[2]=((unsigned char *)p)[5];	\
	((unsigned char *)&tem_d)[3]=((unsigned char *)p)[4];	\
	((unsigned char *)&tem_d)[4]=((unsigned char *)p)[3];	\
	((unsigned char *)&tem_d)[5]=((unsigned char *)p)[2];	\
	((unsigned char *)&tem_d)[6]=((unsigned char *)p)[1];	\
	((unsigned char *)&tem_d)[7]=((unsigned char *)p)[0];	\
	}while(0);

#define bo_buffloat4(f,p)
	do{	\
	double tem_d;	\
	((unsigned char *)&tem_d)[0]=((unsigned char *)p)[3];	\
	((unsigned char *)&tem_d)[1]=((unsigned char *)p)[2];	\
	((unsigned char *)&tem_d)[2]=((unsigned char *)p)[1];	\
	((unsigned char *)&tem_d)[3]=((unsigned char *)p)[0];	\
	}while(0);

#else
#define bo_float4buf(f,p) memcpy((unsigned char *)p,(unsigned char *)(&f),sizeof(float));
#define bo_buffloat4(f,p) memcpy((unsigned char *)&f,(unsigned char *)(p),sizeof(float));
#define bo_doublebuf(f,p) memcpy((unsigned char *)p,(unsigned char *)(&f),sizeof(double));
#define bo_bufdouble(f,p) memcpy((unsigned char *)&f,(unsigned char *)(p),sizeof(double));

#endif





}

#endif
