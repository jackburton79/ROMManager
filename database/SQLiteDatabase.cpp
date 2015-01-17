/*
 * SQLiteDatabase.cpp
 *
 *  Created on: 15/gen/2015
 *      Author: stefano
 */

#include "SQLiteDatabase.h"

#include <sqlite3.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

static int
callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   for(int i = 0; i < argc; i++){
      std::cout << azColName[i] << " = ";
      std::cout << (argv[i] ? argv[i] : "NULL");
   }
   std::cout << std::endl;
   return 0;
}


SQLiteDatabase::SQLiteDatabase()
	:
	fSQLiteHandle(NULL)
{
}


SQLiteDatabase::~SQLiteDatabase()
{
}


int
SQLiteDatabase::Open(const char* name)
{
	return sqlite3_open(name, &fSQLiteHandle);
}


void
SQLiteDatabase::Close()
{
	sqlite3_close(fSQLiteHandle);
}


int
SQLiteDatabase::ExecuteSQL(const char* sql)
{
	char* errorMsg = NULL;
	int status = sqlite3_exec(fSQLiteHandle, sql, callback,
								NULL, &errorMsg);
	if (status != SQLITE_OK) {
		std::cerr << "SQL Error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
	}
	return status;
}
