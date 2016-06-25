#pragma once
#include<winsock2.h>
#include"mysql.h"
#include <vector>
#include "RelicAPI.h"
#include <fstream>

using namespace std;

class CDatabaseManager
{
public:
	CDatabaseManager();
	~CDatabaseManager();
	void initial();
	bool ConnectDb();
	bool LoadFromDb(vector<pair<RelicObj, ObjInfo>>& RelicObjVec);
	bool DisConnectDb();

	enum DbStatus {
		DB_DISCONNECT = 0,
		DB_CONNECT,
		DB_ERROR,
	};

	int m_DbStatus;
private:
	MYSQL m_mysql;
	
};


