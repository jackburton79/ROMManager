/*
 * DatabaseFactory.h
 *
 *  Created on: 16/gen/2015
 *      Author: stefano
 */

#ifndef DATABASEFACTORY_H_
#define DATABASEFACTORY_H_

class Database;
class DatabaseFactory {
public:
	DatabaseFactory();
	~DatabaseFactory();

	Database* GetDatabase(const char* dbType);
};

#endif /* DATABASEFACTORY_H_ */
