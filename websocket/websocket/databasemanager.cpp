#include "databasemanager.h"

CDatabaseManager::CDatabaseManager()
{

}

CDatabaseManager::~CDatabaseManager()
{

}

void CDatabaseManager::initial()
{
	mysql_init(&m_mysql);
}

bool CDatabaseManager::ConnectDb()
{
	bool IsOk = mysql_real_connect(&m_mysql, "localhost", "root", "bkdtmt", "magic_mirror", 3306, NULL, 0);
	if (IsOk)
	{
		m_DbStatus = DB_CONNECT;
	}
	else
	{
		int a = mysql_errno(&m_mysql);
		m_DbStatus = DB_DISCONNECT;
		return false;
	}
	return true;
	return true;
}

bool CDatabaseManager::LoadFromDb(vector<pair<RelicObj, ObjInfo>>& RelicObjVec)
{
	RelicObjVec.clear();
	char sqlcommand[256];
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	//RelicObj mRelicObj;
	//ObjInfo mObjInfo;
	pair<RelicObj, ObjInfo> mPair;
	Mat mMat;
	char tmpstr[256] = {0};
	sprintf_s(sqlcommand, 256, "select * from %s where 1=1", "relic");
	mysql_query(&m_mysql, sqlcommand);
	res = mysql_store_result(&m_mysql);
	char* pBuffer=new char[2048*1024];
	if (res)
	{
		row = mysql_fetch_row(res);
		ifstream file1;

		while (row)
		{
			sprintf_s(tmpstr, 256, row[1]);
			mPair.second.name = tmpstr;
			sprintf_s(tmpstr, 256, row[4]);
			mPair.second.info = tmpstr;
			if (row[5]!=NULL)
			{
				sprintf_s(tmpstr, 256, row[5]);
				mPair.second.year = tmpstr;
			}
			sprintf_s(tmpstr, 256, row[2]);
			mMat = imread(tmpstr);
			mPair.first.Load_Img(mMat);
			sprintf_s(tmpstr, 256, row[3]);
			FILE *mFile;
			mFile=fopen(tmpstr, "rb");
			if (!mFile) continue;
			int num = fread_s(pBuffer, 2048 * 1024, 1, 2048 * 1024, mFile);
			fclose(mFile);
			pBuffer[num] = 0;
			mPair.first.Parse_from_Json(string(pBuffer));
			RelicObjVec.push_back(mPair);

			row = mysql_fetch_row(res);
		}
	}
	if (pBuffer!=NULL)
	{
		delete[] pBuffer;
	}
	if (res != NULL) mysql_free_result(res);
	return true;
}

bool CDatabaseManager::DisConnectDb()
{
	mysql_close(&m_mysql);
	m_DbStatus = DB_DISCONNECT;
	return true;

}
