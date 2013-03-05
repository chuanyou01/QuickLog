// QuickLog.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <sstream>
#include <list>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>


wstring GetCurTime()
{
	time_t tmNow;
	time(&tmNow);
	WCHAR pTime[32] = {0};
	struct tm local_time ;  

	localtime_s(&local_time, &tmNow);
	wcsftime(pTime, 32, _T("%m-%d %H:%M:%S"), &local_time);
	return wstring(pTime);
}




using namespace std;

class gps_position
{
public:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & degrees;

		ar & minutes;

		ar & seconds;
	}

	int id;

	int degrees;

	int minutes;

	float seconds;

public:
	gps_position(){};

	void set(int i, int d, int m, float s)
	{
		id = i;
		degrees = d;
		minutes = m;
		seconds = s;
	};
};

void writeToDB(gps_position& g)
{
	//���ڴ�Ŷ������л�������
	ostringstream oss;

	//ʹ�ö����Ƶķ�ʽ���л�
	boost::archive::binary_oarchive oa(oss);

	//�������л�
	oa << g;

	//������һ�ο������ܷ��ˡ�
	//stringstream���󲢲��ṩֱ�ӻ�ȡ���ڲ�����ĵ�ַ�Ľӿڣ�
	//����Ҳû�а취��ostringstream::str()������basic_stringbuf::str()
	//����ӿڱ�ʹ��std::string�����ȵ��Ǹ����캯������һ��std::string
	//���󷵻أ��������str���ܻ�����л��������������ݣ���Ȼ����
	//�������'\0'
	std::string str = oss.str();
	char* ptr = (char*)str.c_str();

	int size = str.length();

	int nSize = sizeof(gps_position);

	//���ڴ����ݿ��ж������ݣ�Ȼ���ʼ��binary_iarchive
	//��Ϊͬʱ�漰��д�Ͷ�����˱���ʹ��stringstream
	stringstream iss;

	//��ȡ���ݣ�����ʹ��write�Զ����Ƶķ�ʽ��ʼ��iss����
	iss.write((char*)ptr, size);

	boost::archive::binary_iarchive ia(iss);

	gps_position fg;

	//��ԭ����
	ia >> fg;

	cout << fg.degrees << " : " << fg.minutes << " : " << fg.seconds << endl;
	//��Ҫֱ��ʹ��data.set_data((void *)os.str().c_str())��
	//��Ϊos.str()���ص���һ����ʱ���������û����ģ�
	//��������û�б�д�뵽���ݿ���
}

void loadData()
{
	//�����ݿ�
	/*Db db(NULL, 0);
	u_int32_t oFlags = DB_RDONLY;
	try 
	{
		db.open(NULL,
			"test.db",
			NULL,
			DB_BTREE,
			oFlags,
			0);
	}
	catch(DbException &e) 
	{
		std::cout << e.what() << std::endl;
		return;
	}
	catch(std::exception &e) 
	{
		std::cout << e.what() << std::endl;
		return;
	}

	Dbt key, data;
	Dbc *cursor;

	memset(&key, 0, sizeof(Dbt));
	memset(&data, 0, sizeof(Dbt));

	db.cursor(NULL, &cursor, 0);

	while(cursor->get(&key, &data, DB_NEXT) == 0)
	{
		//���ڴ����ݿ��ж������ݣ�Ȼ���ʼ��binary_iarchive
		//��Ϊͬʱ�漰��д�Ͷ�����˱���ʹ��stringstream
		stringstream iss;

		//��ȡ���ݣ�����ʹ��write�Զ����Ƶķ�ʽ��ʼ��iss����
		iss.write((char*)data.get_data(), data.get_size());

		boost::archive::binary_iarchive ia(iss);

		gps_position g;

		//��ԭ����
		ia >> g;

		cout << g.degrees << " : " << g.minutes << " : " << g.seconds << endl;
	}

	cursor->close();
	db.close(0);*/
}

int _tmain(int argc, _TCHAR* argv[])
{
	gps_position g;
	g.set(0, 35, 59, 24.567f);
	writeToDB(g);
}
/*
int _tmain(int argc, _TCHAR* argv[])
{
	string strSvr = "192.168.1.12";
	MXHANDLE hd = MX_INVALID_TREEHANDLE;
	try
	{
		wprintf(_T("Begin time is %s"), GetCurTime().c_str());
		
		int nRet = OpenKey(strSvr, "MXSE", "1", hd);
		if (nRet!=MD_OK)
		{
			throw nRet;
		}
		char pPath[MAX_PATH] = {0};
		GetTempPathA(MAX_PATH, pPath);
		string strTmpPath = pPath;
		string strPath = pPath;
		strPath.append("\\mx_1_export");

		SetTimeout(300);
		nRet = ExportSubTree(hd, strPath, true);
		if (nRet!=MD_OK)
		{
			throw nRet;
		}
		SetTimeout(24);

		list<string> lstFile;
		lstFile.push_back(strPath);
		//lstFile.push_back("mx_1_export");

		CSimpleZip sZip;
		sZip.Add("c:\\mxtest.zip", lstFile, strTmpPath, false);

		sZip.Extract("c:\\", "c:\\mxtest.zip");

		TREEDBFILEHANDLE hdFile;
		nRet = TDB_OpenFile("c:\\tdbfile", hdFile, OTDB_CREATENEW);
		if (nRet!=MD_OK)
		{
			throw nRet;
		}

		SetTimeout(300);
		nRet = TDB_ImportSubTree(hdFile, "c:\\mx_1_export", true);
		if (nRet!=MD_OK)
		{
			throw nRet;
		}
		SetTimeout(24);

		wprintf(_T("End time is %s"), GetCurTime().c_str());
	}
	catch(int& nRet)
	{
		printf("Error id is %d \n", nRet);
	}
	
	return 0;
}

*/