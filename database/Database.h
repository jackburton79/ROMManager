/*
 * Database.h
 *
 *  Created on: 15/gen/2015
 *      Author: stefano
 */

#ifndef DATABASE_H_
#define DATABASE_H_

class Database {
public:
	Database();
	virtual ~Database();

	virtual int Open(const char* fileName) = 0;
	virtual void Close() = 0;
	virtual int ExecuteSQL(const char* sql) = 0;
};

#endif /* DATABASE_H_ */
