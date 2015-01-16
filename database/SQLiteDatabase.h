/*
 * SQLiteDatabase.h
 *
 *  Created on: 15/gen/2015
 *      Author: stefano
 */

#ifndef SQLITEDATABASE_H_
#define SQLITEDATABASE_H_

#include "Database.h"

struct sqlite3;
class SQLiteDatabase : public Database {
public:
	SQLiteDatabase();
	virtual ~SQLiteDatabase();
	virtual int Open(const char* name);
	virtual void Close();
	virtual int ExecuteSQL(const char* sql);
private:
	sqlite3 *fSQLiteHandle;
};

#endif /* SQLITEDATABASE_H_ */
