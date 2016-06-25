#pragma once
#include "RelicObj.hpp"
#include "RelicScn.hpp"
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
class RelicAPI
{
public:
	RelicAPI();
	~RelicAPI();
	static string detect(Mat img);
private:

};

